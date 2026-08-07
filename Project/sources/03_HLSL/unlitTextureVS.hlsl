
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{
    float weight =
    In.BoneWeights.x +
    In.BoneWeights.y +
    In.BoneWeights.z +
    In.BoneWeights.w;
    
    float4 skinnedPosition = float4(0.0f, 0.0f, 0.0f, 0.0f);

    if (weight > 0.0f)
    {
        skinnedPosition +=
    mul(In.Position, BoneMatrices[In.BoneIndices.x])
    * In.BoneWeights.x;

        skinnedPosition +=
    mul(In.Position, BoneMatrices[In.BoneIndices.y])
    * In.BoneWeights.y;

        skinnedPosition +=
    mul(In.Position, BoneMatrices[In.BoneIndices.z])
    * In.BoneWeights.z;

        skinnedPosition +=
    mul(In.Position, BoneMatrices[In.BoneIndices.w])
    * In.BoneWeights.w;
    
        skinnedPosition.w = 1.0f;
    }
    else{
        skinnedPosition = In.Position;
    }
    
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    
    Out.Position = mul(skinnedPosition, wvp);
    Out.TexCoord = In.TexCoord;
    Out.Diffuse = In.Diffuse * Material.Diffuse;

	//Out.Position = mul(In.Position, wvp);
	//Out.TexCoord = In.TexCoord;
	//Out.Diffuse = In.Diffuse * Material.Diffuse;
}

