#include "/home/codeleaded/System/Static/Library/WindowEngine.h"
#include "/home/codeleaded/System/Static/Library/DynPlotter.h"

/*
float fn_g(float x){
	return 2.0f * F32_Sigmoid(10.0f * x) - 1.0f;
}
float fn_f(float x){
	return sinf(x);
}
float Function_1D(float x){
	//return x * sinf(x);
	//return F32_SMax(0.001f * x * x,sinf(x),lambda);
	//return expf(lambda * logf(x));

	float y = x;
	for(int i = 0;i<=(int)floorf(lambda);i++){
		y = fn_g(fn_f(y));
	}
	return y;
}
*/


DynPlotter plotter;
float lambda = 0.0f;

static float Lagrange_Yi(int i,float x){
	const Vec2 points_i = *(Vec2*)Vector_Get(&plotter.points,i);

	float p = 1.0f;
	for(int j = 0;j<plotter.points.size;j++){
		const Vec2 points_j = *(Vec2*)Vector_Get(&plotter.points,j);

		if(i == j) continue;
		p *= x - points_j.x;
		p /= points_i.x - points_j.x;
	}
	return p * points_i.y;
}
static float Function0(float x){
	return x * expf(x);
}
static float Function1(float x){
	return x;
}
static float Function2(float x){
	return Math_Nw_LambertW_0(x);
}
static float Function3(float x){
	return Math_Hy_LambertW_0(x);
}
static float Function4(float x){
	float p = 0.0f;
	for(int i = 0;i<plotter.points.size;i++){
		p += Lagrange_Yi(i,x);
	}
	return p;
}

static void Setup(AlxWindow* w){
	plotter = DynPlotter_New(Rect_New(
		(Vec2){ 10.0f,10.0f },
		(Vec2){ GetWidth() - 20.0f,GetHeight() - 20.0f }
	));

	//DynPlotter_Add_Fn(&plotter,(DynPlotter_Function){ Function0,GREEN });
	//DynPlotter_Add_Fn(&plotter,(DynPlotter_Function){ Function1,RED });
	//DynPlotter_Add_Fn(&plotter,(DynPlotter_Function){ Function2,BLUE });
	//DynPlotter_Add_Fn(&plotter,(DynPlotter_Function){ Function3,YELLOW });
	DynPlotter_Add_Fn(&plotter,(DynPlotter_Function){ Function4,CYAN });
}
static void Update(AlxWindow* w){
	DynPlotter_Update(&plotter,w->Strokes,GetMouse());
	plotter.box.d.x = w->Width - 20.0f;
	plotter.box.d.y = w->Height - 20.0f;

    if(Stroke(ALX_KEY_UP).DOWN){
		lambda += 1.0f * w->ElapsedTime;
	}else if(Stroke(ALX_KEY_DOWN).DOWN){
		lambda -= 1.0f * w->ElapsedTime;
	}

	Clear(BLUE);
	DynPlotter_Render(&plotter,WINDOW_STD_ARGS);

	const Vec2 wm = DynPlotter_ToWorld(&plotter,GetMouse());
	CStr_RenderAlxFontf(WINDOW_STD_ARGS,GetAlxFont(),0.0f,0.0f,WHITE,"P: X: %f, Y: %f",wm.x,wm.y);
	CStr_RenderAlxFontf(WINDOW_STD_ARGS,GetAlxFont(),0.0f,GetAlxFont()->CharSizeY,WHITE,"Lambda: %f",lambda);
}
static void Delete(AlxWindow* w){
	DynPlotter_Free(&plotter);
}

int main(){
    if(Create("Geogebra 2.1",2500,1200,1,1,Setup,Update,Delete))
        Start();
    return 0;
}