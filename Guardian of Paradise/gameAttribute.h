//게임 전용 속성들을 모아둔 일종의 구조체. 나중에 기능확장을 대비해서 클레스로 구현하였다.
#pragma once



// Game Player attribute;
class gameAttribute 
{
private:
	float Hp;
	//최대 체력
	float mHp;

	float MP;
	//최대 마나
	float mMP;

	float atk;
	//마법 공격력
	float mAtk;

	float def;
	//마법 방어력
	float mDef;

	//돈
	float money;
	//공속
	float atkSpeed;
	//경험치
	float exprience;
public:

	inline float getHP(){return Hp;}
	inline void setHP(float HP){ this->Hp = HP; }
	inline float getMaxHp(){ return mHp; }
	inline void setMaxHp(float mHp){ this->mHp = mHp; }
	inline float getMP(){ return MP; }
	inline void setMP(float MP){ this->MP = MP; }
	inline float getMaxMP(){ return mMP; }
	inline void setMaxMP(float mMP){ this->mMP = mMP; }
	inline float getAtk(){ return atk; }
	inline void setAtk(float atk)	{ this->atk = atk; }
	inline float getMagicAtk()	{ return mAtk; }
	inline void setMagicAtk(float mAtk){ this->mAtk = mAtk; }
	inline float getDef(){ return def; }
	inline void setDef(float def)	{ this->def = def; }
	inline float getMagicDef()	{ return mDef; }
	inline void setMagicDef(float mDef){ this->mDef = mDef; }
	inline float getMoney(){ return money; }
	inline void setMoney(float money){ this->money = money; }
	inline float geExp(){ return exprience; }
	inline void setExp(float exprience){ this->exprience = exprience; }
	inline float getAtkSpeed(){ return atkSpeed; }
	inline void setAtkSpeed(float atkSpeed){ this->atkSpeed = atkSpeed; }

	inline void setBasicGAttribute(float HP, float MP, float ATK, float DEF, float atkSpeed)
	{
		setHP(HP); setMP(MP);setMaxHp(HP); setMaxMP(MP); setAtk(ATK); setDef(DEF); setAtkSpeed(atkSpeed);
	}
	gameAttribute();
	~gameAttribute();

};

