struct VS_INPUT
{
	float4 position: POSITION;
	float4 position1: POSITION1;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
	float3 color1: COLOR1;
};

cbuffer constant: register(b0)
{
	//using rowmajor convention
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_proj;

	unsigned int m_time;
};

VS_OUTPUT vsmain( VS_INPUT input )
{
	// y in (0,1) means upper half of screen
	//if (position.y > 0 && position.y < 1) {
	//	position.x += 0.25f; //skew them by 0.25 along +ve x direction
	//}
	//Bottom right quadrant of screen
	//if (position.y > -1 && position.y < 0 && position.x > 0 && position.x < 1) {
	//	position.y += 0.25f; //skew them by 0.25 along +ve y direction
	//}
	//Top left quadrant of screen 
	//if (position.y > 0 && position.y < 1 && position.x >-1 && position.x < 0) {
	//	position.y -= 0.25f; //skew them by 0.25 along +ve x direction
	//}
	//return position;

	VS_OUTPUT output = (VS_OUTPUT)0;
	//output.position = lerp(input.position, input.position1, (sin(m_time / 1000.0f) * 1.0f) / 2.0f);
	
	//Vertex in world space coordinates
	output.position = mul(input.position, m_world);
	//World space to view space coordinates
	output.position = mul(output.position, m_view);
	//View space to projection space
	output.position = mul(output.position, m_proj);

	output.color = input.color;
	output.color1 = input.color1;

	return output;
}