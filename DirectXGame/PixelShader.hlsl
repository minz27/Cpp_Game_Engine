struct PS_INPUT //==VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
	unsigned int m_time;
};

//Pixel Shader is the last shader in pipeline. It receives output of vertex shader as input
float4 psmain(PS_INPUT input) : SV_TARGET
{
	return float4(lerp(input.color, input.color1, (sin(m_time / 500.0f) * 1.0f) / 2.0f), 1.0f);
}