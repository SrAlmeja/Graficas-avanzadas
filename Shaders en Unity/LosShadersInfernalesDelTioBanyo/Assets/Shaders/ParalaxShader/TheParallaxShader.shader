Shader "Unlit/TheParallaxShader"
{
 Properties {
        _MainTex ("Texture", 2D) = "white" {}
        _BumpMap ("BumpMap", 2D) = "bump" {}
        _Parallax ("Parallax", Range(0, 0.08)) = 0.02
    }
    SubShader {
        Tags { "RenderType"="Opaque" }
        LOD 100

        CGPROGRAM
        #pragma surface surf Standard vertex:vert
        #pragma target 3.0

        struct Input {
            float2 uv_MainTex;
            float2 uv_BumpMap;
            float3 worldPos;
            float3 worldNormal;
        };

        sampler2D _MainTex;
        sampler2D _BumpMap;
        float _Parallax;

        void vert(inout appdata_full v) {
            float3 worldPos = mul(unity_ObjectToWorld, v.vertex);
            float3 worldNormal = normalize(mul(unity_ObjectToWorld, v.normal));

            float3 viewDir = normalize(UnityWorldSpaceViewDir(worldPos));

            float height = tex2D(_BumpMap, v.uv).r;
            float2 offset = viewDir.xy * (height * _Parallax);

            worldPos.xy += offset;

            v.vertex = mul(unity_WorldToObject, worldPos);
            v.worldPos = worldPos;
            v.worldNormal = worldNormal;
        }

        void surf (Input IN, inout SurfaceOutputStandard o) {
            o.Albedo = tex2D(_MainTex, IN.uv_MainTex).rgb;
            o.Metallic = 0;
            o.Smoothness = 0.5;
            o.Normal = UnpackNormal(tex2D(_BumpMap, IN.uv_BumpMap));
            o.Alpha = 1;
        }
        ENDCG
    }
    FallBack "Diffuse"
}