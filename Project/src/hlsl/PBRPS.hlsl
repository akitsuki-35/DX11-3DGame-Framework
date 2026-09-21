/*------------------------------------------------------------
	PBRピクセルシェーダー
------------------------------------------------------------*/
#include "Common.hlsl"
#include "CookTranceSub.hlsl"

Texture2D gTexture : register(t0); // 0番テクスチャ
Texture2D gTextureRoughness : register(t2); // 2番テクスチャ
Texture2D gTextureMetalness : register(t3); // 3番テクスチャ

SamplerState gSamplerState : register(s0); // 0番サンプラー

float CalculateDiffuseFromFresnel(float3 N, float3 L, float3 V);
float CalculateCookTranceSpecular(float3 L, float3 V, float3 N, float smooth, float metalic);

static const float PI = 3.1415926f;

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    // 法線計算
    float4 normal = normalize(In.Normal);
    
    // アルベドカラー
    float4 albedo = float4(0.0f, 0.0f, 0.0f, 0.0f);
    
    // テクスチャが存在する場合はテクスチャカラー、無ければマテリアルカラーを取得
    if (Material.TextureEnable)
    {
        albedo = gTexture.Sample(gSamplerState, In.TexCoord);
    }
    else
    {
        albedo = Material.Diffuse;
    }
    
    // スペキュラカラー
    float3 speColor = albedo.rgb;
    
    // 滑らかさを取得
    float smooth = gTextureRoughness.Sample(gSamplerState, In.TexCoord).r * 2.0f - 1.0f;
    smooth *= Parameter.x;
    smooth = saturate(smooth);
    
    // 金属度を取得
    float metalic = gTextureMetalness.Sample(gSamplerState, In.TexCoord).r * 2.0f - 1.0f;
    metalic *= Parameter.y;
    metalic = saturate(metalic);
    
    // カメラへのベクトルを計算
    float3 eyev = CameraPosition.xyz - In.WorldPosition.xyz;
    eyev = normalize(eyev);
    
    float3 lit = 0;
    
    int loop = (int)Parameter.z;
    
    for (int i = 0; i < loop; i++)
    {
        // 光源へのベクトル
        float4 lv = normalize(-Light.Direction);
        
        // フレネル反射を考慮した拡散計算
        float diffuseFromFresnel = CalculateDiffuseFromFresnel(normal.xyz, lv.xyz, eyev);

        // 正規化ランバート拡散反射
        float nl = saturate(dot(normal.xyz, lv.xyz));
        float3 light = nl + Light.Diffuse.rgb / PI;
        
        // 最終的な拡散反射光を計算
        float3 diffuse = albedo.rgb * diffuseFromFresnel * Light.Diffuse.rgb * light;
        
        // 鏡面反射を計算
        float3 specular = CalculateCookTranceSpecular(lv.xyz, eyev, normal.xyz, smooth, metalic) * Light.Diffuse.rgb * light;
        
        specular *= lerp(float3(1.0f, 1.0f, 1.0f), speColor, metalic);
        
        lit += diffuse * (1.0f - smooth) + specular;
    }
    
    float3 light = lit * In.Diffuse.rgb;
    float3 ambient = Light.Ambient.rgb * Light.Diffuse.rgb * albedo.rgb;
    
    outDiffuse.rgb = light + ambient;
    outDiffuse.a = albedo.a * In.Diffuse.a;
}

float CalculateDiffuseFromFresnel(float3 N, float3 L, float3 V)
{
    float nl = saturate(dot(N, L));
    float nv = saturate(dot(N, V));
    
    return (nl * nv);
}

float CalculateCookTranceSpecular(float3 L, float3 V, float3 N, float smooth, float metalic)
{
    float3 H = normalize(L + V);
    
    float nh = saturate(dot(N, H));
    float vh = saturate(dot(V, H));
    float nl = saturate(dot(N, L));
    float nv = saturate(dot(N, V));

    float D = CalculateBeckmann(smooth, nh);
    float F = CalculateFresnel(metalic, vh);
    float G = CalculateGeometricDamping(nh, nv, nl, vh);
        
    float m = max(PI * nv * nh, 0.00001f);
    
    return max(F * D * G / m, 0.0f);
}