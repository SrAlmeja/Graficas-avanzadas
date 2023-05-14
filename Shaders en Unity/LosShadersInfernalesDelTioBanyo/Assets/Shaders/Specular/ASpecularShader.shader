Shader "Custom/ASpecularShader" {
    Properties {
        _MainTex ("_Albedo", 2D) = "white" {}
        _SpecularTex ("Specular", 2D) = "white" {}
        _Shiness ("_Shininess", Range(0.01, 1)) = 0.078125
        _Color ("_Color", Color) = (1,1,1,1)
        }
 
    SubShader {
        Tags { "RenderType"="Opaque" }
        LOD 100
 
        CGPROGRAM
        #pragma surface surf Standard

        
 
        sampler2D _MainTex;
 
        struct Input {
            float2 uv_MainTex;
            float3 worldPos;
            float3 worldNormal;
        };
        fixed4 _Color;
        float _Shiness;
        sampler2D specularTex;
 
        void surf (Input IN, inout SurfaceOutputStandard o) {
            float3 camPos = _WorldSpaceCameraPos;
            float3 viewDir = normalize(camPos - IN.worldPos);
            
            fixed4 c = tex2D (_MainTex, IN.uv_MainTex) *  _Color;
            o.Alpha = c.a;
            
            o.Albedo = tex2D(_MainTex, IN.uv_MainTex).rgb * viewDir;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
