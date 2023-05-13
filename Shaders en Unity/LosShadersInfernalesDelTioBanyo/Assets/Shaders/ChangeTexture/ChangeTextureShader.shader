Shader "Custom/SwitchTextureShader" {
    Properties {
        _MainTex1 ("Texture 1", 2D) = "white" {}
        _MainTex2 ("Texture 2", 2D) = "white" {}
        _speed ("speed", Range(0,10)) = 1
    }
    SubShader {
        Tags {"RenderType"="Opaque" }
        LOD 100

        Pass {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag
            #include "UnityCG.cginc"

            struct appdata {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            sampler2D _MainTex1;
            sampler2D _MainTex2;
            float _blendValue;
            float _speed;

            v2f vert (appdata v) {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }

            fixed4 frag (v2f i) : SV_Target {
                _blendValue = cos(_Time.y) * 3 + 2;
                fixed4 col1 = tex2D(_MainTex1, i.uv);
                fixed4 col2 = tex2D(_MainTex2, i.uv);
                return lerp(col1, col2, _blendValue);
            }
            ENDCG
        }
    }
    FallBack "Diffuse"
}
