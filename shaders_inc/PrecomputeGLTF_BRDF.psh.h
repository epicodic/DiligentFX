"#include \"FullScreenTriangleVSOutput.fxh\"\n"
"#include \"GLTF_PBR_PrecomputeCommon.fxh\"\n"
"\n"
"#define NUM_SAMPLES 256u\n"
"\n"
"float2 IntegrateBRDF( float Roughness, float NoV, uint NumSamples )\n"
"{\n"
"    float3 V;\n"
"    V.x = sqrt( 1.0 - NoV * NoV ); // sin\n"
"    V.y = 0.0;\n"
"    V.z = NoV; // cos\n"
"    const float3 N = float3(0.0, 0.0, 1.0);\n"
"    float A = 0;\n"
"    float B = 0;\n"
"    for( uint i = 0; i < NumSamples; i++ )\n"
"    {\n"
"        float2 Xi = Hammersley2D( i, NumSamples );\n"
"        float3 H = ImportanceSampleGGX( Xi, Roughness, N );\n"
"        float3 L = 2.0 * dot( V, H ) * H - V;\n"
"        float NoL = saturate( L.z );\n"
"        float NoH = saturate( H.z );\n"
"        float VoH = saturate( dot( V, H ) );\n"
"        if( NoL > 0 )\n"
"        {\n"
"            //float G     = G_Smith( Roughness, NoV, NoL );\n"
"            // Visibility = G(v,l,a) / (4 * (n,v) * (n,l))\n"
"            float G     = SmithGGXVisibilityCorrelated( NoL, NoV, Roughness ) * 4.0 * NoL * NoV;\n"
"            float G_Vis = G * VoH / (NoH * NoV);\n"
"            float Fc = pow( 1 - VoH, 5.0 );\n"
"            A += (1.0 - Fc) * G_Vis;\n"
"            B += Fc * G_Vis;\n"
"        }\n"
"    }\n"
"    return float2( A, B ) / float(NumSamples);\n"
"}\n"
"\n"
"void PrecomputeBRDF_PS(FullScreenTriangleVSOutput VSOut,\n"
"                       out float2 f2BRDF_LUT : SV_Target)\n"
"{\n"
"    float NdotV           = VSOut.f2NormalizedXY.x;\n"
"    float linearRoughness = VSOut.f2NormalizedXY.y;\n"
"    f2BRDF_LUT = IntegrateBRDF(linearRoughness, NdotV, NUM_SAMPLES);\n"
"}\n"
