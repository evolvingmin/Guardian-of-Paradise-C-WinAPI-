#include "stdafx.h"
#include "gameQuest.h"
#include "addtionalMapInfo.h"
#include "EnviromentObject.h"
#include "EffectAndItemObject.h"
#include "Player.h"
int gameQuest::uniqueGenerateNum = 0;

gameQuest::gameQuest()
{
	_questType = QUEST_NONE;
	_uniqueNum = ++uniqueGenerateNum;
	_isActive = true;
}


gameQuest::~gameQuest()
{
}
bool gameQuest::operator == (const gameQuest& s)
{
	if (s._uniqueNum == _uniqueNum)
		return true;
	else
		return false;
}

void gameQuest::setRelatedGameObject(vector<tagObjectInfo> objectSet)
{

	if (_isActive)
	{
		for (int i = 0; i < objectSet.size(); i++)
		{
			if (_uniqueNum == objectSet[i].questIndex)
			{
				EnviromentObject* enviromentObject;
				EffectAndItemObject* items;
				switch (objectSet[i].objectSelect)
				{
				case OBJECT_ITEM_SWORD:
				case OBJECT_ITEM_KEY:
				case OBJECT_ITEM_HEALTH:
				case OBJECT_ITEM_LUCA:
				case OBJECT_ITEM_LUCA_UP:
				case OBJECT_ITEM_FOREST_EMBLEM:
					items = new EffectAndItemObject;
					items->init(objectSet[i]);
					_isCalledCheck = true;
					break;
				default:
					enviromentObject = new EnviromentObject;
					enviromentObject->init(objectSet[i]);
					switch (_questType)
					{
					case QUEST_DOOR_KEY_REQUIRED:
						_isCalledCheck = true;
						break;
					default:
						_isCalledCheck = false;
						break;
					} // end of switch(_questType)
					break; // end of default whinin switch(objectSet[i].objectSelect)
				} // end of switch (objectSet[i].objectSelect)
			} //end of if (_uniqueNum == objectSet[i].questIndex)
		}
	}

}
void gameQuest::checkQuestCondition()
{
	if (_isActive)
	{
		int buttonCount = 0;
		int clickedButtonCount = 0;

		int numberLockCount = 0;
		int matchedLockCount = 0;

		vectorGameObjectList vQuestData = GOBJECTMANAGER->getVectorData();
		Player* player = NULL;
		switch (_questType)
		{
		case QUEST_DOOR_MONSTER_DESTROY:
			if (GOBJECTMANAGER->findGameObject("monster") == NULL)
			{
				_isActive = false;
				searchAndDestroy("door_condition");
			}
			break;
		case QUEST_DOOR_NUMBER_MATCHED:
			for (vectorGameObjectIter iter = vQuestData.begin(); iter != vQuestData.end(); iter++)
			{
				if ((*iter)->getTag() == "numberLock")
				{
					EnviromentObject* tempLock= (EnviromentObject*)(*iter);
					if (tempLock->getHitCount() == tempLock->getObjectInfo().goalNumber)
						matchedLockCount++;
					numberLockCount++;
				}
			}
			if (numberLockCount == matchedLockCount)
			{
				_isActive = false;
				searchAndDestroy("door_condition");
			}
			break;
		case QUEST_DOOR_BUTTON_SOLVED:

			for (vectorGameObjectIter iter = vQuestData.begin(); iter != vQuestData.end(); iter++)
			{
				if ((*iter)->getTag() == "button")
				{
					EnviromentObject* tempButton = (EnviromentObject*)(*iter);
					if (tempButton->getButtonClicked())
						clickedButtonCount++;
					buttonCount++;
				}
			}
			if (buttonCount == clickedButtonCount)
			{
				_isActive = false;
				searchAndDestroy("door_condition");
			}
			break;
		case QUEST_DOOR_KEY_REQUIRED:
			player = (Player*)GOBJECTMANAGER->findGameObject("player");
			for (int i = ITEMMAX - 1; i >= 0; i--)
			{
				if (player->getItems()[i] == ITEM_KEY)
				{
					player->getItems()[i] = ITEM_NONE;
					_isActive = false;
					SOUNDMANAGER->play("kachi01",1.0f);
					searchAndDestroy("door_key");
					break;
				}

			}
			break;
		case QUEST_BOSS_DESTROY: break;
		case QUEST_NPC_TALK: 
			_isActive = true;
			break;
		case QUEST_ITEM_CONSUMED: 
			_isActive = false;
			break;
		}


	}
}

bool gameQuest::searchAndDestroy(string tag)
{
	vectorGameObjectList vQuestData = GOBJECTMANAGER->getVectorData();
	for (vectorGameObjectIter iter = vQuestData.begin(); iter != vQuestData.end(); iter++)
	{
		if ((*iter)->getTag() == tag)
		{
			EnviromentObject* targetObject = (EnviromentObject*)(*iter);
			if (targetObject->getObjectInfo().questIndex == _uniqueNum)
			{
				targetObject->setDestroy(true);
				SOUNDMANAGER->play("hit03", 1.0f);
				return true;
			}
		}
	}
	return false;
}
