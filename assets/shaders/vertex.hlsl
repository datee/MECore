struct Matrices {
    float4x4 model;
    float4x4 view;
    float4x4 proj;
};

ConstantBuffer<Matrices> matrices : register(b0);

struct VertInput {
    float3 position : POSITION;
};

struct VertOutput {
    float4 position : SV_POSITION;
};

VertOutput vertex(VertInput input) {
    VertOutput output;
    // output.position = mul((matrices.proj * matrices.view * matrices.model), float4(input.position, 1.0));
    // output.position = mul(matrices.model * matrices.view * matrices.proj, float4(input.position, 1.0));
	output.position = float4(input.position, 1.0);
    return output;
}
