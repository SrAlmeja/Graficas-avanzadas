Shader "Custom/ASpecularShader" {
    Properties {
        _MainTex ("Albedo (RGB)", 2D) = "white" {}
        _SpecularTex ("Specular (RGB)", 2D) = "white" {}
        _Shininess ("Shininess", Range(0.01, 1)) = 0.078125
        _SpecularFactor ("Specular Factor", Range(0, 1)) = 0.5
    }
 
    SubShader {
        Tags { "RenderType"="Opaque" }
        LOD 100
 
        CGPROGRAM
        #pragma surface surf Standard
 
        sampler2D _MainTex;
        sampler2D _SpecularTex;
        float _Shininess;
        float _SpecularFactor;
 
        struct Input {
            float2 uv_MainTex;
            float3 worldPos;
            float3 worldNormal;
            float3 worldViewDir;
            float3 worldRefl;
        };
 
        void surf (Input IN, inout SurfaceOutputStandard o) {
            float3 viewDir = normalize(IN.worldViewDir);
            float3 normal = normalize(IN.worldNormal);
            float3 refl = normalize(IN.worldRefl);
 
            float NdotV = max(0, dot(normal, viewDir));
            float3 halfwayDir = normalize(viewDir + refl);
            float NdotH = max(0, dot(normal, halfwayDir));
 
            float spec = pow(NdotH, _Shininess);

            o.Normal = Input.normal
            o.Albedo = tex2D(_MainTex, IN.uv_MainTex).rgb;
            o.Metallic = 0;
            o.Smoothness = 1 - NdotV;
            o.Normal = normal;
            o.Specular = spec * _SpecularFactor;
            o.Emission = tex2D(_SpecularTex, IN.uv_MainTex).rgb * o.Specular;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
