Shader "Unlit/BlurVertical"
{
    Properties
    {
        _MainTex ("Texture", 2D) = "white" {}
        _kernelSize ("kernel Size",  Range(1, 30)) = 5
        _TextureWidth ("texture Width", Range(1, 4096)) = 1024
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 100
        
        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };

            sampler2D _MainTex;
            float _kernelSize;
            float _TextureWidth;

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }

            fixed4 frag (v2f i) : SV_Target
            {
                float texelSize = 1.0 / _TextureWidth;
                fixed4 result = fixed4(0.0,0.0,0.0,0.0);

                for (int j = - _kernelSize; j <= _kernelSize; j++)
                {
                    float weight = float(j);
                    fixed4 sample = tex2D(_MainTex, i.uv + fixed2(0.0, weight * texelSize));
                    result += sample;
                }
                result /= _kernelSize * 2+1;
                return result;
            }
            ENDCG
        }
    }
}
