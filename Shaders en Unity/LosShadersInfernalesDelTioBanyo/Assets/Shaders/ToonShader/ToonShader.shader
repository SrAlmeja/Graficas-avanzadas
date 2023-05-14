Shader "Custom/ToonShader" 
{
	Properties {
		_MainTex ("Texture", 2D) = "white" {}
		_Ramp ("Gradient", 2D) = "white" {}
	}
	SubShader {
		Tags {"Queue"="Transparent" "RenderType"="Opaque"}
		LOD 100

		CGPROGRAM
		#pragma surface surf Toon

		sampler2D _MainTex;
		sampler2D _Ramp;

		struct Input {
			float2 uv_MainTex;
			float2 uv_Ramp;
			float3 worldPos;
		};

		void surf (Input IN, inout SurfaceOutputStandard o) {
			// Sample albedo texture
			o.Albedo = tex2D(_MainTex, IN.uv_MainTex).rgb;

			// Calculate light direction and color
			float3 lightDir, lightColor;
			float distanceAtten, shadowAtten;
			MainLight_float(IN.worldPos, lightDir, lightColor, distanceAtten, shadowAtten);

			// Calculate diffuse lighting
			float NdotL = dot(IN.worldNormal, lightDir);
			float3 diffuse = o.Albedo * max(0, NdotL) * lightColor;

			// Sample gradient texture and apply to lighting
			float3 ramp = tex2D(_Ramp, IN.uv_Ramp).rgb;
			float3 toon = round(diffuse * 4) / 4;
			o.Emission = ramp * toon;

			// Apply distance attenuation
			o.Emission *= distanceAtten;

			// Apply shadow attenuation
			o.Alpha *= shadowAtten;
		}
		ENDCG
	}
	FallBack "Diffuse"
}