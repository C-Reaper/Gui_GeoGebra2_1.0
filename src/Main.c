#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/Random.h"
#include "/home/codeleaded/System/Static/Library/TransformedView.h"


float lambda = 0.0f;
TransformedView tv;

float Function_1D(float x){
	//return x * sinf(x);
	//return F32_SMax(0.001f * x * x,sinf(x),lambda);
	return expf(lambda * logf(x));
}

void Setup(AlxWindow* w){
	tv = TransformedView_New((Vec2){ GetWidth(),GetHeight() });
}

void Update(AlxWindow* w){
	TransformedView_HandlePanZoom(&tv,window.Strokes,GetMouse());

	if(Stroke(ALX_KEY_UP).DOWN){
		lambda += 1.0f * w->ElapsedTime;
	}else if(Stroke(ALX_KEY_DOWN).DOWN){
		lambda -= 1.0f * w->ElapsedTime;
	}

	Clear(BLACK);

	Vec2 wvls = { 0.0f,TransformedView_ScreenWorldY(&tv,0.0f) };
	Vec2 wvle = { 0.0f,TransformedView_ScreenWorldY(&tv,GetHeight()) };
	Vec2 whls = { TransformedView_ScreenWorldX(&tv,0.0f),0.0f };
	Vec2 whle = { TransformedView_ScreenWorldX(&tv,GetWidth()),0.0f };

	Vec2 svls = TransformedView_WorldScreenPos(&tv,wvls);
	Vec2 svle = TransformedView_WorldScreenPos(&tv,wvle);
	Vec2 shls = TransformedView_WorldScreenPos(&tv,whls);
	Vec2 shle = TransformedView_WorldScreenPos(&tv,whle);

	RenderLine(svls,svle,WHITE,1.0f);
	RenderLine(shls,shle,WHITE,1.0f);

	Vec2 PosBefore = {};
	for(int i = 0;i<GetWidth();i++){
		const float x = TransformedView_ScreenWorldX(&tv,i);
		const float y = Function_1D(x);
		const Vec2 Pos = { i,TransformedView_WorldScreenY(&tv,-y) };
		
		RenderLine(PosBefore,Pos,RED,1.0f);
		PosBefore = Pos;
	}

	Vec2 p = TransformedView_ScreenWorldPos(&tv,GetMouse());
	CStr_RenderAlxFontf(WINDOW_STD_ARGS,GetAlxFont(),0.0f,0.0f,WHITE,"P: X: %f, Y: %f",p.x,p.y);
	CStr_RenderAlxFontf(WINDOW_STD_ARGS,GetAlxFont(),0.0f,GetAlxFont()->CharSizeY,WHITE,"Lambda: %f",lambda);
}

void Delete(AlxWindow* w){
	
}

int main(){
    if(Create("Geogebra 2.1",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}