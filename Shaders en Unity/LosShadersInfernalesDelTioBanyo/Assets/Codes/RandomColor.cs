using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using Random = UnityEngine.Random;

public class RandomColor : MonoBehaviour
{
    public  Color Color;
    public float Time;
    
    public Renderer renderer;

    private void Start()
    {
        StartCoroutine(ChangeColor(Time));
    }

    IEnumerator ChangeColor(float time)
    {
        while (true)
        {
            Color = Random.ColorHSV();
            renderer.material.SetColor("_Color", Color);
            yield return new WaitForSeconds(time);
        }
    }
         
}
