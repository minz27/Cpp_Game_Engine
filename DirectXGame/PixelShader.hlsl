struct PS_INPUT //==VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
};
//Pixel Shader is the last shader in pipeline. It receives output of vertex shader as input
float4 psmain(PS_INPUT input) : SV_TARGET
{
	return float4(input.color, 1.0f);
}