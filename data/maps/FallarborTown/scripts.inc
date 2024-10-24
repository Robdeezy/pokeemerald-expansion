.set LOCALID_RIVAL, 5

FallarborTown_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition:
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	call_if_unset FLAG_FALLARBOR_RIVAL, Fallarbor_SetRival
	end

FallarborTown_EventScript_ExpertM::
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal::
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl::
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman::
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill::
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, CRY_MODE_NORMAL
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign::
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign::
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign::
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome:
	.string "Something's happening,\n"
	.string "and I don't like it!\p"
	.string "I've seen shady characters wandering\n"
	.string "in and out of PROF. COZMO's home…$"

FallarborTown_Text_RegionKnownForMeteors:
	.string "This region's been known for meteors\n"
	.string "since the olden days.\p"
	.string "They say METEOR FALLS was gouged out\n"
	.string "by a falling meteorite long ago.$"

FallarborTown_Text_MyPreciousAzurill:
	.string "See! Take a look!\n"
	.string "This is my precious AZURILL!\p"
	.string "It's slick and smooth and plushy, too!$"

FallarborTown_Text_Azurill:
	.string "AZURILL: Rooreelooo.$"

FallarborTown_Text_HaveYouChallengedFlannery:
	.string "Have you already challenged FLANNERY,\n"
	.string "the LEADER of LAVARIDGE GYM?\p"
	.string "The girl's grandfather was famous.\n"
	.string "He was one of the ELITE FOUR in the\l"
	.string "POKéMON LEAGUE at one point.\p"
	.string "It wouldn't surprise me to see FLANNERY\n"
	.string "become a great TRAINER in her own\l"
	.string "right.$"

FallarborTown_Text_BattleTentSign:
	.string "BATTLE TENT FALLARBOR SITE\n"
	.string "“May the Greatest Teams Gather!”$"

FallarborTown_Text_TownSign:
	.string "FALLARBOR TOWN\n"
	.string "“A farm community with small gardens.”$"

FallarborTown_Text_MoveTutorSign:
	.string "MOVE TUTOR'S HOUSE\n"
	.string "“New moves taught to POKéMON.”$"

Fallarbor_SetRival:
	setflag FLAG_FALLARBOR_RIVAL
	return

Fallarbor_EventScript_RivalTrigger1::
	setvar VAR_TEMP_1, 1
	goto Fallarbor_EventScript_RivalEncounter
	end

Fallarbor_EventScript_RivalTrigger2::
	setvar VAR_TEMP_1, 2
	goto Fallarbor_EventScript_RivalEncounter
	end

Fallarbor_EventScript_RivalEncounter::
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
	waitmovement 0
	addobject LOCALID_RIVAL
	checkplayergender
	call_if_eq VAR_RESULT, MALE, Fallarbor_EventScript_PlayMayMusic
	call_if_eq VAR_RESULT, FEMALE, Fallarbor_EventScript_PlayBrendanMusic
	delay 65
	call_if_eq VAR_TEMP_1, 1, Fallarbor_EventScript_RivalEnter1
	call_if_eq VAR_TEMP_1, 2, Fallarbor_EventScript_RivalEnter2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
	waitmovement 0
	call_if_eq VAR_TEMP_1, 1, Fallarbor_EventScript_SetRivalPos1
	call_if_eq VAR_TEMP_1, 2, Fallarbor_EventScript_SetRivalPos2
	checkplayergender
	goto_if_eq VAR_RESULT, MALE, Fallarbor_EventScript_BattleMay
	goto_if_eq VAR_RESULT, FEMALE, Fallarbor_EventScript_BattleBrendan
	releaseall
	end

Fallarbor_EventScript_PlayMayMusic::
	playbgm MUS_ENCOUNTER_MAY, TRUE
	return

Fallarbor_EventScript_PlayBrendanMusic::
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
	return

Fallarbor_EventScript_RivalEnter1::
	applymovement LOCALID_RIVAL, Fallarbor_Movement_RivalEnter1
	waitmovement 0
	return

Fallarbor_EventScript_RivalEnter2::
	applymovement LOCALID_RIVAL, Fallarbor_Movement_RivalEnter2
	waitmovement 0
	return

Fallarbor_Movement_RivalEnter1:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_left
	walk_left
	walk_left
	step_end

Fallarbor_Movement_RivalEnter2:
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Fallarbor_EventScript_SetRivalPos1::
	setobjectxyperm LOCALID_RIVAL, 1, 9
	return

Fallarbor_EventScript_SetRivalPos2::
	setobjectxyperm LOCALID_RIVAL, 1, 10
	return

Fallarbor_EventScript_BattleMay::
	msgbox Fallarbor_Text_MayIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Fallarbor_EventScript_BattleMayTreecko
	case 1, Fallarbor_EventScript_BattleMayTorchic
	case 2, Fallarbor_EventScript_BattleMayMudkip
	end

Fallarbor_EventScript_BattleMayTreecko::
	trainerbattle_no_intro TRAINER_MAY_FALLARBOR_TREECKO, Fallarbor_Text_MayDefeat
	goto Fallarbor_EventScript_DefeatedMay
	end

Fallarbor_EventScript_BattleMayTorchic::
	trainerbattle_no_intro TRAINER_MAY_FALLARBOR_TORCHIC, Fallarbor_Text_MayDefeat
	goto Fallarbor_EventScript_DefeatedMay
	end

Fallarbor_EventScript_BattleMayMudkip::
	trainerbattle_no_intro TRAINER_MAY_FALLARBOR_MUDKIP, Fallarbor_Text_MayDefeat
	goto Fallarbor_EventScript_DefeatedMay
	end

Fallarbor_EventScript_DefeatedMay::
	msgbox Fallarbor_Text_MayPresentForYou, MSGBOX_DEFAULT
	call Fallarbor_EventScript_GiveExpertBelt
	msgbox Fallarbor_Text_MayExplainExpertBelt, MSGBOX_DEFAULT
	goto Fallarbor_EventScript_RivalExit
	end

Fallarbor_EventScript_BattleBrendan::
	msgbox Fallarbor_Text_BrendanIntro, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, Fallarbor_EventScript_BattleBrendanTreecko
	case 1, Fallarbor_EventScript_BattleBrendanTorchic
	case 2, Fallarbor_EventScript_BattleBrendanMudkip
	end

Fallarbor_EventScript_BattleBrendanTreecko::
	trainerbattle_no_intro TRAINER_BRENDAN_FALLARBOR_TREECKO, Fallarbor_Text_BrendanDefeat
	goto Fallarbor_EventScript_DefeatedBrendan
	end

Fallarbor_EventScript_BattleBrendanTorchic::
	trainerbattle_no_intro TRAINER_BRENDAN_FALLARBOR_TORCHIC, Fallarbor_Text_BrendanDefeat
	goto Fallarbor_EventScript_DefeatedBrendan
	end

Fallarbor_EventScript_BattleBrendanMudkip::
	trainerbattle_no_intro TRAINER_BRENDAN_FALLARBOR_MUDKIP, Fallarbor_Text_BrendanDefeat
	goto Fallarbor_EventScript_DefeatedBrendan
	end

Fallarbor_EventScript_DefeatedBrendan::
	msgbox Fallarbor_Text_BrendanIllGiveYouThis, MSGBOX_DEFAULT
	call Fallarbor_EventScript_GiveExpertBelt
	msgbox Fallarbor_Text_BrendanExplainExpertBelt, MSGBOX_DEFAULT
	goto Fallarbor_EventScript_RivalExit
	end

Fallarbor_EventScript_RivalExit::
	closemessage
	call_if_eq VAR_TEMP_1, 1, Fallarbor_EventScript_SetRivalPos1
	call_if_eq VAR_TEMP_1, 2, Fallarbor_EventScript_SetRivalPos2
	delay 30
	call_if_eq VAR_TEMP_1, 1, Fallarbor_EventScript_RivalExit1
	call_if_eq VAR_TEMP_1, 2, Fallarbor_EventScript_RivalExit2
	removeobject LOCALID_RIVAL
	setvar VAR_FALLARBOR_TOWN_STATE, 1
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

Fallarbor_EventScript_RivalExit1::
	applymovement OBJ_EVENT_ID_PLAYER, Fallarbor_Movement_PlayerWatchRivalExit1
	applymovement LOCALID_RIVAL, Fallarbor_Movement_RivalExit1
	waitmovement 0
	return

Fallarbor_EventScript_RivalExit2::
	applymovement OBJ_EVENT_ID_PLAYER, Fallarbor_Movement_PlayerWatchRivalExit2
	applymovement LOCALID_RIVAL, Fallarbor_Movement_RivalExit2
	waitmovement 0
	return

Fallarbor_Movement_PlayerWatchRivalExit1:
	delay_16
	walk_in_place_faster_down
	delay_8
	walk_in_place_faster_left
	step_end

Fallarbor_Movement_PlayerWatchRivalExit2:
	delay_16
	walk_in_place_faster_up
	delay_8
	walk_in_place_faster_left
	step_end

Fallarbor_Movement_RivalExit1:
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

Fallarbor_Movement_RivalExit2:
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end


Fallarbor_Text_MayIntro:
	.string "MAY: {PLAYER}{KUN}!\n"
	.string "I was looking for you!\p"
	.string "How is your Pokedex coming along?\n"
	.string "Lets battle to test our strength!\p"
	.string "Ready with your POKéMON?\n"
	.string "Here I come!$"

Fallarbor_Text_MayDefeat:
	.string "Achah!\n"
	.string "{PLAYER}{KUN}, you're strong!\p"
	.string "I was worried that you might be\n"
	.string "slacking with your training.$"

Fallarbor_Text_MayPresentForYou:
	.string "MAY: But I had absolutely nothing to\n"
	.string "worry about! Keep it up!\p"
	.string "And, here! I have a present for you.$"

Fallarbor_Text_BrendanIntro:
	.string "BRENDAN: {PLAYER}! So this is where\n"
	.string "you've been looking for POKéMON?\p"
	.string "Let me see test your strength.\n"
	.string "Now!\n"
	.string "It's a battle, en garde!$"

Fallarbor_Text_BrendanDefeat:
	.string "Hmm…\n"
	.string "You've still got room to improve.$"

Fallarbor_Text_BrendanIllGiveYouThis:
	.string "BRENDAN: I'd say you're good enough\n"
	.string "to use this in battle.$"

Fallarbor_EventScript_GiveExpertBelt::
	giveitem ITEM_EXPERT_BELT
	return

Fallarbor_Text_MayExplainExpertBelt:
	.string "MAY: This is an item to give to pokemon\n"
	.string "it boosts the power of super effective\l"
	.string "moves.\p"
	.string "{PLAYER}{KUN}.\p"
	.string "Catch you later!$"

Fallarbor_Text_BrendanExplainExpertBelt:
	.string "BRENDAN: This is an item to give to\n"
	.string "pokemon, it boosts the power of super\l"
	.string "effective moves.\p"
	.string "Anyway, see you later.$"
