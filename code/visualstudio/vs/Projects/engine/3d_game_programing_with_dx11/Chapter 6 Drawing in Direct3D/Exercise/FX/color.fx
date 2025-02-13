//***************************************************************************************
// color.fx by Frank Luna (C) 2011 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject
{
	float4x4 gWorldViewProj; 
};

//struct VertexIn
//{
//	float3 PosL  : POSITION;
//    float4 Color : COLOR;
//};

// exercise 6.1
//struct VertexIn
//{
//	float3 PosL  : POSITION;
//	float3 Tangent  : TANGENT;
//	float3 Nromal  : NORMAL;
//	float3 Tex0  : TEXCOORD0;
//	float3 Tex1  : TEXCOORD1;
//    float4 Color : COLOR;
//};

//exercise 6.2
struct VertexIn
{
	float3 PosL  : POSITION;
    float4 Color : COLOR;
};

struct VertexOut
{
	float4 PosH  : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	
	// Just pass vertex color into the pixel shader.
    vout.Color = vin.Color;
    //vout.Color = float4(1.0, 0.0, 0.0, 1.0);
    
    return vout;
}

float4 PS(VertexOut pin) : SV_Target
{
    return pin.Color;
}

technique11 ColorTech
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS() ) );
    }
}
