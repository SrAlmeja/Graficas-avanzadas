Shader "Unlit/USB_Simple_Color"
{
    Properties
    {
        // Aqui se colocan las propiedades del Shader
        _MainTex ("Texture", 2D) = "white" {}
        _Color ("Color", Color) = (1,1,1,1)
        _Specular ("Specular", Range(0.0, 1.1)) = 0.3
        _Factor ("Color Factor", Float) = 0.3
        _Cid ("Color id", Int) = 2
        _vPos ("Vertex Position", Vector) = (0,0,0,1)
        [Toggle] _TryMeToggle("TryMe", Float) = 0 //No hace nada
        [Toggle] _Enable ("Enable ?", Float) = 0
    }
    SubShader
    {
        // Aqui se coloca la configuracion del SubShader
        Tags { "RenderType"="Opaque" }
        LOD 100

        Pass
        {
            CGPROGRAM
            /*De aquí CGPROGRAM "End CG" es el programa Cg aqui se escribe el codigo HLSL*/ 
            #pragma vertex vert
            #pragma fragment frag
            #pragma shader_feature _ENABLE_ON
            

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                UNITY_FOG_COORDS(1)
                float4 vertex : SV_POSITION;
                
            };

            sampler2D _MainTex;
            float4 _MainTex_ST;
            float4 _Color;
            half _Specular;
            float _Factor;
            int _Cid;
            float4 _vPose;
            

            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = TRANSFORM_TEX(v.uv, _MainTex);
                return o;
            }

            half4 frag (v2f i) : SV_Target
            {
                half4 col = tex2D(_MainTex, i.uv);

                //generamos la condición
                #if _ENABLE_ON
                    return col;
                #else
                    return col.rgb *= _Color.rgb
                #endif
            }
            
            ENDCG
        }
    }
}