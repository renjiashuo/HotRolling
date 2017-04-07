#pragma once
//软约束罚分宏定义

/*#define THICK_FORWARD_RULE_SCORE    100
#define THICK_BACKWARD_RULE_SCORE   100
#define WIDTH_FORWARD_RULE_SCORE    100
#define WIDTH_BACKWARD_RULE_SCORE   100
#define HEAT_TEMP_JUMP_RULE_SCORE   100
#define AFFT_TEMP_JUMP_RULE_SCORE   100
#define COIL_TEMP_JUMP_RULE_SCORE   100
#define HARD_GROUP_JUMP_RULE_SCORE  100*/
struct rule_score
{
//----------厚度跳跃

	const int THICK_FORWARD_RULE_SCORE_1 = 0;//厚度前跳
	const int THICK_FORWARD_RULE_SCORE_2 = 0;//厚度前跳
	const int THICK_FORWARD_RULE_SCORE_3 = 0;//厚度前跳

	const int THICK_BACKWARD_RULE_SCORE_1 = 0;//厚度后跳
	const int THICK_BACKWARD_RULE_SCORE_2 = 0;//厚度后跳
	const int THICK_BACKWARD_RULE_SCORE_3 = 0;//厚度后跳

//----------宽度跳跃

	const int WIDTH_FORWARD_RULE_SCORE_1 = 0;//宽度前跳
	const int WIDTH_FORWARD_RULE_SCORE_2 = 0;//宽度前跳
	const int WIDTH_FORWARD_RULE_SCORE_3 = 0;//宽度前跳

	const int WIDTH_BACKWARD_RULE_SCORE_1 = 0;//宽度后跳
	const int WIDTH_BACKWARD_RULE_SCORE_2 = 0;//宽度后跳
	const int WIDTH_BACKWARD_RULE_SCORE_3 = 0;//宽度后跳

//----------出炉温度跳跃

	const int HEAT_TEMP_JUMP_RULE_SCORE_1 = 0;//出炉温度跳跃
	const int HEAT_TEMP_JUMP_RULE_SCORE_2 = 0;//出炉温度跳跃
	const int HEAT_TEMP_JUMP_RULE_SCORE_3 = 0;//出炉温度跳跃

//----------终轧温度跳跃

	const int AFFT_TEMP_JUMP_RULE_SCORE_1 = 0;//终轧温度跳跃
	const int AFFT_TEMP_JUMP_RULE_SCORE_2 = 0;//终轧温度跳跃
	const int AFFT_TEMP_JUMP_RULE_SCORE_3 = 0;//终轧温度跳跃

//----------卷取温度跳跃

	const int COIL_TEMP_JUMP_RULE_SCORE_1 = 0;//卷取温度跳跃
	const int COIL_TEMP_JUMP_RULE_SCORE_2 = 0;//卷取温度跳跃
	const int COIL_TEMP_JUMP_RULE_SCORE_3 = 0;//卷取温度跳跃

//----------硬度组跳跃

	const int HARD_GROUP_JUMP_RULE_SCORE_1 = 0;//硬度组跳跃
	const int HARD_GROUP_JUMP_RULE_SCORE_2 = 0;//硬度组跳跃
	const int HARD_GROUP_JUMP_RULE_SCORE_3 = 0;//硬度组跳跃

};