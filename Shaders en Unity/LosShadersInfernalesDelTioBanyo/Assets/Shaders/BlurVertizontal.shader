Shader "Unlit/BlurVertizontal"
{
   Properties
	{
		_MainTex("Texture", 2D) = "white" {}
		_KernelSizeX("Kernel Size X", Range(1, 30)) = 5
		_KernelSizeY("Kernel Size Y", Range(1, 30)) = 5
		_TextureWidth("Texture Width", Range(1, 4096)) = 1024
		_TextureHeight("Texture Height", Range(1, 4096)) = 1024
	}

		SubShader
	{
		Tags { "RenderType" = "Opaque" }
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
			float _KernelSizeX;
			float _KernelSizeY;
			float _TextureWidth;
			float _TextureHeight;

			v2f vert(appdata v)
			{
				v2f o;
				o.vertex = UnityObjectToClipPos(v.vertex);
				o.uv = v.uv.xy;
				return o;
			}

			fixed4 frag(v2f i) : SV_Target
			{
				float texelSizeX = 1.0 / _TextureWidth;
				float texelSizeY = 1.0 / _TextureHeight;
				fixed4 result = fixed4(0.0, 0.0, 0.0, 0.0);

				// blur vertical
				for (int j = -_KernelSizeY; j <= _KernelSizeY; j++)
				{
					float weight = float(j);
					fixed4 sample = tex2D(_MainTex, i.uv + fixed2(0.0, weight * texelSizeY));
					result += sample;
				}

				// blur horizontal
				for (int j = -_KernelSizeX; j <= _KernelSizeX; j++)
				{
					float weight = float(j);
					fixed4 sample = tex2D(_MainTex, i.uv + fixed2(weight * texelSizeX, 0.0));
					result += sample;
				}
				result /= (_KernelSizeX + _KernelSizeY) * 2 + 1;

				return result;
			}
			ENDCG
		}
	}
}
