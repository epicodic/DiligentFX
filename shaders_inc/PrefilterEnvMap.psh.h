"#include \"GLTF_PBR_PrecomputeCommon.fxh\"\n"
"\n"
"TextureCube  g_EnvironmentMap;\n"
"SamplerState g_EnvironmentMap_sampler;\n"
"\n"
"cbuffer FilterAttribs\n"
"{\n"
"    float4x4 g_Rotation;\n"
"\n"
"    float    g_Roughness;\n"
"    float    g_EnvMapDim;\n"
"    uint     g_NumSamples;\n"
"    float    Dummy;\n"
"}\n"
"\n"
"// https://blog.selfshadow.com/publications/s2013-shading-course/karis/s2013_pbs_epic_notes_v2.pdf\n"
"float3 PrefilterEnvMap( float Roughness, float3 R )\n"
"{\n"
"    float3 N = R;\n"
"    float3 V = R;\n"
"    float3 PrefilteredColor = float3(0.0, 0.0, 0.0);\n"
"    float TotalWeight = 0.0;\n"
"    for( uint i = 0; i < g_NumSamples; i++ )\n"
"    {\n"
"        float2 Xi = Hammersley2D( i, g_NumSamples );\n"
"        float3 H  = ImportanceSampleGGX( Xi, Roughness, N );\n"
"        float3 L  = 2.0 * dot( V, H ) * H - V;\n"
"        float NoL = clamp( dot( N, L ), 0.0, 1.0 );\n"
"        if( NoL > 0 )\n"
"        {\n"
"            PrefilteredColor += g_EnvironmentMap.SampleLevel(g_EnvironmentMap_sampler, L, 0.0).rgb * NoL;\n"
"            TotalWeight += NoL;\n"
"        }\n"
"    }\n"
"    return PrefilteredColor / TotalWeight;\n"
"}\n"
"\n"
"\n"
"void main(in float4  Pos      : SV_Position,\n"
"          in float3  WorldPos : WORLD_POS,\n"
"          out float4 Color    : SV_Target)\n"
"{		\n"
"	float3 R = normalize(WorldPos);\n"
"    Color.rgb = PrefilterEnvMap(g_Roughness, R);\n"
"}\n"
