struct VS_INPUT
{
	float4 position: POSITION;
	float3 color: COLOR;
};

struct VS_OUTPUT
{
	float4 position: SV_POSITION;
	float3 color: COLOR;
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
	output.position = input.position;
	output.color = input.color;

	return output;
}