"#ifndef _GLTF_PBR_STRUCTURES_FXH_\n"
"#define _GLTF_PBR_STRUCTURES_FXH_\n"
"\n"
"#ifdef __cplusplus\n"
"\n"
"#   ifndef CHECK_STRUCT_ALIGNMENT\n"
"        // Note that defining empty macros causes GL shader compilation error on Mac, because\n"
"        // it does not allow standalone semicolons outside of main.\n"
"        // On the other hand, adding semicolon at the end of the macro definition causes gcc error.\n"
"#       define CHECK_STRUCT_ALIGNMENT(s) static_assert( sizeof(s) % 16 == 0, \"sizeof(\" DILIGENT_STRINGIFY(s) \") is not multiple of 16\" )\n"
"#   endif\n"
"\n"
"#endif\n"
"\n"
"#ifndef MAX_NUM_JOINTS\n"
"#   define MAX_NUM_JOINTS 128u\n"
"#endif\n"
"\n"
"#define  PBR_WORKFLOW_METALLIC_ROUGHNESS  0\n"
"#define  PBR_WORKFLOW_SPECULAR_GLOSINESS  1\n"
"\n"
"struct GLTFNodeShaderTransforms\n"
"{\n"
"	float4x4 NodeMatrix;\n"
"	float4x4 JointMatrix[MAX_NUM_JOINTS];\n"
"\n"
"	int      JointCount;\n"
"    float    Dummy0;\n"
"    float    Dummy1;\n"
"    float    Dummy2;\n"
"};\n"
"#ifdef CHECK_STRUCT_ALIGNMENT\n"
"	CHECK_STRUCT_ALIGNMENT(GLTFNodeShaderTransforms);\n"
"#endif\n"
"\n"
"\n"
"struct GLTFRendererShaderParameters\n"
"{\n"
"	float AverageLogLum;\n"
"	float MiddleGray;\n"
"    float WhitePoint;\n"
"	float PrefilteredCubeMipLevels;\n"
"\n"
"	float IBLScale;\n"
"	int   DebugViewType;\n"
"    float OcclusionStrength;\n"
"    float EmissionScale;\n"
"};\n"
"#ifdef CHECK_STRUCT_ALIGNMENT\n"
"	CHECK_STRUCT_ALIGNMENT(GLTFRendererShaderParameters);\n"
"#endif\n"
"\n"
"struct GLTFMaterialShaderInfo\n"
"{\n"
"	float4  BaseColorFactor;\n"
"	float4  EmissiveFactor;\n"
"	float4  SpecularFactor;\n"
"\n"
"	int     Workflow;\n"
"	float   BaseColorTextureUVSelector;\n"
"	float   PhysicalDescriptorTextureUVSelector;\n"
"	float   NormalTextureUVSelector; \n"
"\n"
"	float   OcclusionTextureUVSelector;\n"
"	float   EmissiveTextureUVSelector;\n"
"	float   MetallicFactor;\n"
"	float   RoughnessFactor;\n"
"\n"
"	int     UseAlphaMask;	\n"
"	float   AlphaMaskCutoff;\n"
"    float   Dummy0;\n"
"    float   Dummy1;\n"
"};\n"
"#ifdef CHECK_STRUCT_ALIGNMENT\n"
"	CHECK_STRUCT_ALIGNMENT(GLTFMaterialShaderInfo);\n"
"#endif\n"
"\n"
"#endif // _GLTF_PBR_STRUCTURES_FXH_\n"
