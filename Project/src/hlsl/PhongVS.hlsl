/*------------------------------------------------------------
	フォンシェーディング頂点シェーダー
------------------------------------------------------------*/
#include "Common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    Out = (PS_IN) 0;
    
    // 頂点座標を行列で変換して出力
    matrix wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    Out.Position = mul(In.Position, wvp);
    
    // 法線の回転
    // 法線ベクトルの平行移動成分を0にする
    float4 normal = float4(In.Normal.xyz, 0.0f);
    
    // 法線をワールド行列で回転
    float4 worldNormal = mul(normal, World);
    
    // 回転後の法線を正規化
    worldNormal = normalize(worldNormal);
    
    // 回転後の法線を出力
    Out.Normal = worldNormal;
    
    // 出力
    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord;
    
    // ワールド変換した頂点座標を出力
    Out.WorldPosition = mul(In.Position, World);
}