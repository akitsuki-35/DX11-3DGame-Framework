// マイクロファセット分布関数
float CalculateBeckmann(float smooth, float nh)
{
    float D = 0.0f;
    
    if (nh > 0.0f && smooth > 0.0f)
    {
        float smo2 = smooth * smooth;
        float nh2 = nh * nh;
        float nh4 = nh2 * nh2;
    
        // 指数計算
        float ex = -(1.0f - nh2) / (smo2 * nh2);
    
        // 分母計算
        float PI = 3.14159265f;
        float bun = PI * smo2 * nh4;
        
        D = exp(ex) / bun;
    }
    
    return D;
}

// フレネル反射項
float CalculateFresnel(float metal, float hv)
{
    // Schlick近似
    metal = lerp(0.04f, 1.0f, metal); // metal = 0.04f～1.0f
    float F = metal + (1.0f - metal) * pow(1.0f - hv, 5.0f);
    
    return F;
}

// 幾何減衰率
float CalculateGeometricDamping(float nh, float nv, float nl, float vh)
{
    vh = max(vh, 0.0001f);
    float G = min(1.0f, min(2.0f * nh / vh, 2.0f * nh * nl / vh));
    
    return G;
}