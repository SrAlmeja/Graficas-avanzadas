using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class TextureChanger : MonoBehaviour
{
    public float changerTime;
    private Renderer _render;
    private Material _mat;
    
    // Start is called before the first frame update
    void Awake()
    {
        _render = GetComponent<Renderer>();
        _mat = _render.material;
    }

    private void Start()
    {
        StartCoroutine(ChangeTexture(changerTime));
    }

    IEnumerator ChangeTexture(float time)
    {
        while (true)
        {
            float blendValue = Mathf.Sin(time) * 0.5f + 0.5f;
            _mat.SetFloat("_blendValue", blendValue);
            yield return new WaitForSeconds(time);
        }
    }
}
