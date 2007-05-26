// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

#include "timer.h"
#include "nullpo.h"
#include "malloc.h"

#include "skill.h"
#include "map.h"
#include "clif.h"
#include "pc.h"
#include "status.h"
#include "pet.h"
#include "flooritem.h"
#include "mob.h"
#include "npc.h"
#include "homun.h"
#include "battle.h"
#include "party.h"
#include "itemdb.h"
#include "script.h"
#include "intif.h"
#include "log.h"
#include "chrif.h"
#include "guild.h"
#include "showmsg.h"
#include "utils.h"
#include "socket.h"
#include "grfio.h"
#define SKILLUNITTIMER_INVERVAL	100


const struct skill_name_db skill_names[] = {
 { AC_CHARGEARROW, "CHARGEARROW", "Arrow_Repel" } ,
 { AC_CONCENTRATION, "CONCENTRATION", "Improve_Concentration" } ,
 { AC_DOUBLE, "DOUBLE", "Double_Strafe" } ,
 { AC_MAKINGARROW, "MAKINGARROW", "Arrow_Crafting" } ,
 { AC_OWL, "OWL", "Owl's_Eye" } ,
 { AC_SHOWER, "SHOWER", "Arrow_Shower" } ,
 { AC_VULTURE, "VULTURE", "Vulture's_Eye" } ,
 { ALL_RESURRECTION, "RESURRECTION", "Resurrection" } ,
 { AL_ANGELUS, "ANGELUS", "Angelus" } ,
 { AL_BLESSING, "BLESSING", "Blessing" } ,
 { AL_CRUCIS, "CRUCIS", "Signum_Crusis" } ,
 { AL_CURE, "CURE", "Cure" } ,
 { AL_DECAGI, "DECAGI", "Decrease_AGI" } ,
 { AL_DEMONBANE, "DEMONBANE", "Demon_Bane" } ,
 { AL_DP, "DP", "Divine_Protection" } ,
 { AL_HEAL, "HEAL", "Heal" } ,
 { AL_HOLYLIGHT, "HOLYLIGHT", "Holy_Light" } ,
 { AL_HOLYWATER, "HOLYWATER", "Aqua_Benedicta" } ,
 { AL_INCAGI, "INCAGI", "Increase_AGI" } ,
 { AL_PNEUMA, "PNEUMA", "Pneuma" } ,
 { AL_RUWACH, "RUWACH", "Ruwach" } ,
 { AL_TELEPORT, "TELEPORT", "Teleport" } ,
 { AL_WARP, "WARP", "Warp_Portal" } ,
 { AM_ACIDTERROR, "ACIDTERROR", "Acid_Terror" } ,
 { AM_AXEMASTERY, "AXEMASTERY", "Axe_Mastery" } ,
 { AM_BERSERKPITCHER, "BERSERKPITCHER", "Aid_Berserk_Potion" } ,
 { AM_BIOETHICS, "BIOETHICS", "Bioethics" } ,
 { AM_BIOTECHNOLOGY, "BIOTECHNOLOGY", "Biotechnology" } ,
 { AM_CALLHOMUN, "CALLHOMUN", "Call_Homunculus" } ,
 { AM_CANNIBALIZE, "CANNIBALIZE", "Summon_Flora" } ,
 { AM_CP_ARMOR, "ARMOR", "Synthetic_Armor" } ,
 { AM_CP_HELM, "HELM", "Biochemical_Helm" } ,
 { AM_CP_SHIELD, "SHIELD", "Synthetized_Shield" } ,
 { AM_CP_WEAPON, "WEAPON", "Alchemical_Weapon" } ,
 { AM_CREATECREATURE, "CREATECREATURE", "Creature_Creation" } ,
 { AM_CULTIVATION, "CULTIVATION", "Cultivation" } ,
 { AM_DEMONSTRATION, "DEMONSTRATION", "Bomb" } ,
 { AM_DRILLMASTER, "DRILLMASTER", "Drillmaster" } ,
 { AM_FLAMECONTROL, "FLAMECONTROL", "Flame_Control" } ,
 { AM_HEALHOMUN, "HEALHOMUN", "Heal_Homunculus" } ,
 { AM_LEARNINGPOTION, "LEARNINGPOTION", "Potion_Research" } ,
 { AM_PHARMACY, "PHARMACY", "Prepare_Potion" } ,
 { AM_POTIONPITCHER, "POTIONPITCHER", "Aid_Potion" } ,
 { AM_REST, "REST", "Vaporize" } ,
 { AM_RESURRECTHOMUN, "RESURRECTHOMUN", "Homunculus_Resurrection" } ,
 { AM_SPHEREMINE, "SPHEREMINE", "Summon_Marine_Sphere" } ,
 { ASC_BREAKER, "BREAKER", "Soul_Destroyer" } ,
 { ASC_CDP, "CDP", "Create_Deadly_Poison" } ,
 { ASC_EDP, "EDP", "Enchant_Deadly_Poison" } ,
 { ASC_HALLUCINATION, "HALLUCINATION", "Hallucination_Walk" } ,
 { ASC_KATAR, "KATAR", "Advanced_Katar_Mastery" } ,
 { ASC_METEORASSAULT, "METEORASSAULT", "Meteor_Assault" } ,
 { AS_CLOAKING, "CLOAKING", "Cloaking" } ,
 { AS_ENCHANTPOISON, "ENCHANTPOISON", "Enchant_Poison" } ,
 { AS_GRIMTOOTH, "GRIMTOOTH", "Grimtooth" } ,
 { AS_KATAR, "KATAR", "Katar_Mastery" } ,
 { AS_LEFT, "LEFT", "Lefthand_Mastery" } ,
 { AS_POISONREACT, "POISONREACT", "Poison_React" } ,
 { AS_RIGHT, "RIGHT", "Righthand_Mastery" } ,
 { AS_SONICBLOW, "SONICBLOW", "Sonic_Blow" } ,
 { AS_SPLASHER, "SPLASHER", "Venom_Splasher" } ,
 { AS_VENOMDUST, "VENOMDUST", "Venom_Dust" } ,
 { BA_APPLEIDUN, "APPLEIDUN", "Song_of_Lutie" } ,
 { BA_ASSASSINCROSS, "ASSASSINCROSS", "Impressive_Riff" } ,
 { BA_DISSONANCE, "DISSONANCE", "Unchained_Serenade" } ,
 { BA_FROSTJOKE, "FROSTJOKE", "Unbarring_Octave" } ,
 { BA_MUSICALLESSON, "MUSICALLESSON", "Music_Lessons" } ,
 { BA_MUSICALSTRIKE, "MUSICALSTRIKE", "Melody_Strike" } ,
 { BA_POEMBRAGI, "POEMBRAGI", "Magic_Strings" } ,
 { BA_WHISTLE, "WHISTLE", "Perfect_Tablature" } ,
 { BD_ADAPTATION, "ADAPTATION", "Amp" } ,
 { BD_DRUMBATTLEFIELD, "DRUMBATTLEFIELD", "Battle_Theme" } ,
 { BD_ENCORE, "ENCORE", "Encore" } ,	
 { BD_ETERNALCHAOS, "ETERNALCHAOS", "Down_Tempo" } ,
 { BD_INTOABYSS, "INTOABYSS", "Power_Cord" } ,
 { BD_LULLABY, "LULLABY", "Lullaby" } ,
 { BD_RAGNAROK, "RAGNAROK", "Ragnarok" } ,
 { BD_RICHMANKIM, "RICHMANKIM", "Mental_Sensing" } ,
 { BD_RINGNIBELUNGEN, "RINGNIBELUNGEN", "Harmonic_Lick" } ,
 { BD_ROKISWEIL, "ROKISWEIL", "Classical_Pluck" } ,
 { BD_SIEGFRIED, "SIEGFRIED", "Acoustic_Rhythm" } ,
 { BS_ADRENALINE, "ADRENALINE", "Adrenaline_Rush" } ,
 { BS_ADRENALINE2, "ADRENALINE2", "Advanced_Adrenaline_Rush" } ,
 { BS_AXE, "AXE", "Smith_Axe" } ,
 { BS_DAGGER, "DAGGER", "Smith_Dagger" } ,
 { BS_ENCHANTEDSTONE, "ENCHANTEDSTONE", "Enchantedstone_Craft" } ,
 { BS_FINDINGORE, "FINDINGORE", "Ore_Discovery" } ,
 { BS_HAMMERFALL, "HAMMERFALL", "Hammer_Fall" } ,
 { BS_HILTBINDING, "HILTBINDING", "Hilt_Binding" } ,
 { BS_IRON, "IRON", "Iron_Tempering" } ,
 { BS_KNUCKLE, "KNUCKLE", "Smith_Knucklebrace" } ,
 { BS_MACE, "MACE", "Smith_Mace" } ,
 { BS_MAXIMIZE, "MAXIMIZE", "Power_Maximize" } ,
 { BS_ORIDEOCON, "ORIDEOCON", "Oridecon_Research" } ,
 { BS_OVERTHRUST, "OVERTHRUST", "Power-Thrust" } ,
 { BS_REPAIRWEAPON, "REPAIRWEAPON", "Weapon_Repair" } ,
 { BS_SKINTEMPER, "SKINTEMPER", "Skin_Tempering" } ,
 { BS_SPEAR, "SPEAR", "Smith_Spear" } ,
 { BS_STEEL, "STEEL", "Steel_Tempering" } ,
 { BS_SWORD, "SWORD", "Smith_Sword" } ,
 { BS_TWOHANDSWORD, "TWOHANDSWORD", "Smith_Two-handed_Sword" } ,
 { BS_WEAPONPERFECT, "WEAPONPERFECT", "Weapon_Perfection" } ,
 { BS_WEAPONRESEARCH, "WEAPONRESEARCH", "Weaponry_Research" } ,
 { CG_ARROWVULCAN, "ARROWVULCAN", "Vulcan_Arrow" } ,
 { CG_HERMODE, "HERMODE", "Wand_of_Hermode" } ,
 { CG_LONGINGFREEDOM, "LONGINGFREEDOM", "Longing_for_Freedom" } ,
 { CG_MARIONETTE, "MARIONETTE", "Marionette_Control" } ,
 { CG_MOONLIT, "MOONLIT", "Sheltering_Bliss" } ,
 { CG_TAROTCARD, "TAROTCARD", "Tarot_Card_of_Fate" } ,
 { CH_CHAINCRUSH, "CHAINCRUSH", "Chain_Crush_Combo" } ,
 { CH_PALMSTRIKE, "PALMSTRIKE", "Raging_Palm_Strike" } ,
 { CH_SOULCOLLECT, "SOULCOLLECT", "Zen" } ,
 { CH_TIGERFIST, "TIGERFIST", "Glacier_Fist" } ,
 { CR_ACIDDEMONSTRATION, "ACIDDEMONSTRATION", "Acid_Demonstration" } ,
 { CR_ALCHEMY, "ALCHEMY", "Alchemy" } ,
 { CR_CULTIVATION, "CULTIVATION", "Plant_Cultivation" } ,
 { CR_SLIMPITCHER, "SLIMPITCHER", "Slim_Pitcher" } ,
 { CR_FULLPROTECTION, "FULLPROTECTION", "Full_Protection" } ,
 { CR_SYNTHESISPOTION, "SYNTHESISPOTION", "Potion_Synthesis" } ,
 { CR_AUTOGUARD, "AUTOGUARD", "Guard" } ,
 { CR_DEFENDER, "DEFENDER", "Defending_Aura" } ,
 { CR_DEVOTION, "DEVOTION", "Sacrifice" } ,
 { CR_GRANDCROSS, "GRANDCROSS", "Grand_Cross" } ,
 { CR_HOLYCROSS, "HOLYCROSS", "Holy_Cross" } ,
 { CR_PROVIDENCE, "PROVIDENCE", "Resistant_Souls" } ,
 { CR_REFLECTSHIELD, "REFLECTSHIELD", "Shield_Reflect" } ,
 { CR_SHIELDBOOMERANG, "SHIELDBOOMERANG", "Shield_Boomerang" } ,
 { CR_SHIELDCHARGE, "SHIELDCHARGE", "Smite" } ,
 { CR_SPEARQUICKEN, "SPEARQUICKEN", "Spear_Quicken" } ,
 { CR_TRUST, "TRUST", "Faith" } ,
 { DC_DANCINGLESSON, "DANCINGLESSON", "Dance_Lessons" } ,
 { DC_DONTFORGETME, "DONTFORGETME", "Slow_Grace" } ,
 { DC_FORTUNEKISS, "FORTUNEKISS", "Lady_Luck" } ,
 { DC_HUMMING, "HUMMING", "Focus_Ballet" } ,
 { DC_SCREAM, "SCREAM", "Dazzler" } ,
 { DC_SERVICEFORYOU, "SERVICEFORYOU", "Gypsy's_Kiss" } ,
 { DC_THROWARROW, "THROWARROW", "Slinging_Arrow" } ,
 { DC_UGLYDANCE, "UGLYDANCE", "Hip_Shaker" } ,
 { GD_APPROVAL, "APPROVAL", "Official_Guild_Approval" } ,
 { GD_BATTLEORDER, "BATTLEORDER", "Battle_Command" } ,
 { GD_DEVELOPMENT, "DEVELOPMENT", "Permanent_Development" } ,
 { GD_EMERGENCYCALL, "EMERGENCYCALL", "Urgent_Call" } ,
 { GD_EXTENSION, "EXTENSION", "Guild_Extension" } ,
 { GD_GLORYGUILD, "GLORYGUILD", "Glory_of_Guild" } ,
 { GD_GLORYWOUNDS, "GLORYWOUNDS", "Glorious_Wounds" } ,
 { GD_GUARDUP, "GUARDUP", "Strengthen_Guardian" } ,
 { GD_LEADERSHIP, "LEADERSHIP", "Great_Leadership" } ,
 { GD_HAWKEYES, "HAWKEYES", "Sharp_Gaze" } ,
 { GD_KAFRACONTRACT, "KAFRACONTRACT", "Contract_with_Kafra" } ,
 { GD_REGENERATION, "REGENERATION", "Regeneration" } ,
 { GD_RESTORE, "RESTORE", "Restoration" } ,
 { GD_SOULCOLD, "SOULCOLD", "Cold_Heart" } ,
 { HP_ASSUMPTIO, "ASSUMPTIO", "Assumptio" } ,
 { HP_BASILICA, "BASILICA", "Basilica" } ,
 { HP_MANARECHARGE, "MANARECHARGE", "Mana_Recharge" } ,
 { HP_MEDITATIO, "MEDITATIO", "Meditatio" } ,
 { HT_ANKLESNARE, "ANKLESNARE", "Ankle_Snare" } ,
 { HT_BEASTBANE, "BEASTBANE", "Beast_Bane" } ,
 { HT_BLASTMINE, "BLASTMINE", "Blast_Mine" } ,
 { HT_BLITZBEAT, "BLITZBEAT", "Blitz_Beat" } ,
 { HT_CLAYMORETRAP, "CLAYMORETRAP", "Claymore_Trap" } ,
 { HT_DETECTING, "DETECTING", "Detect" } ,
 { HT_FALCON, "FALCON", "Falconry_Mastery" } ,
 { HT_FLASHER, "FLASHER", "Flasher" } ,
 { HT_FREEZINGTRAP, "FREEZINGTRAP", "Freezing_Trap" } ,
 { HT_LANDMINE, "LANDMINE", "Land_Mine" } ,
 { HT_REMOVETRAP, "REMOVETRAP", "Remove_Trap" } ,
 { HT_SANDMAN, "SANDMAN", "Sandman" } ,
 { HT_SHOCKWAVE, "SHOCKWAVE", "Shockwave_Trap" } ,
 { HT_SKIDTRAP, "SKIDTRAP", "Skid_Trap" } ,
 { HT_SPRINGTRAP, "SPRINGTRAP", "Spring_Trap" } ,
 { HT_STEELCROW, "STEELCROW", "Steel_Crow" } ,
 { HT_TALKIEBOX, "TALKIEBOX", "Talkie_Box" } ,
 { HW_GANBANTEIN, "GANBANTEIN", "Ganbantein" } ,
 { HW_GRAVITATION, "GRAVITATION", "Gravitation_Field" } ,
 { HW_MAGICCRASHER, "MAGICCRASHER", "Stave_Crasher" } ,
 { HW_MAGICPOWER, "MAGICPOWER", "Mystical_Amplification" } ,
 { HW_NAPALMVULCAN, "NAPALMVULCAN", "Napalm_Vulcan" } ,
 { HW_SOULDRAIN, "SOULDRAIN", "Soul_Drain" } ,
 { ITM_TOMAHAWK, "TOMAHAWK", "Tomahawk_Throwing" } ,
 { KN_AUTOCOUNTER, "AUTOCOUNTER", "Counter_Attack" } ,
 { KN_BOWLINGBASH, "BOWLINGBASH", "Bowling_Bash" } ,
 { KN_BRANDISHSPEAR, "BRANDISHSPEAR", "Brandish_Spear" } ,
 { KN_CAVALIERMASTERY, "CAVALIERMASTERY", "Cavalier_Mastery" } ,
 { KN_PIERCE, "PIERCE", "Pierce" } ,
 { KN_RIDING, "RIDING", "Peco_Peco_Ride" } ,
 { KN_SPEARBOOMERANG, "SPEARBOOMERANG", "Spear_Boomerang" } ,
 { KN_SPEARMASTERY, "SPEARMASTERY", "Spear_Mastery" } ,
 { KN_SPEARSTAB, "SPEARSTAB", "Spear_Stab" } ,
 { KN_TWOHANDQUICKEN, "TWOHANDQUICKEN", "Twohand_Quicken" } ,
 { LK_AURABLADE, "AURABLADE", "Aura_Blade" } ,
 { LK_BERSERK, "BERSERK", "Frenzy" } ,
 { LK_CONCENTRATION, "CONCENTRATION", "Spear_Dynamo" } ,
 { LK_FURY, "FURY", "Fury_2" } ,
 { LK_HEADCRUSH, "HEADCRUSH", "Traumatic_Blow" } ,
 { LK_JOINTBEAT, "JOINTBEAT", "Vital_Strike" } ,
 { LK_PARRYING, "PARRYING", "Parry" } ,
 { LK_SPIRALPIERCE, "SPIRALPIERCE", "Clashing_Spiral" } ,
 { LK_TENSIONRELAX, "TENSIONRELAX", "Relax" } ,
 { MC_CARTREVOLUTION, "CARTREVOLUTION", "Cart_Revolution" } ,
 { MC_CHANGECART, "CHANGECART", "Change_Cart" } ,
 { MC_DISCOUNT, "DISCOUNT", "Discount" } ,
 { MC_IDENTIFY, "IDENTIFY", "Item_Appraisal" } ,
 { MC_INCCARRY, "INCCARRY", "Enlarge_Weight_Limit" } ,
 { MC_LOUD, "LOUD", "Crazy_Uproar" } ,
 { MC_MAMMONITE, "MAMMONITE", "Mammonite" } ,
 { MC_OVERCHARGE, "OVERCHARGE", "Overcharge" } ,
 { MC_PUSHCART, "PUSHCART", "Pushcart" } ,
 { MC_VENDING, "VENDING", "Vending" } ,
 { MG_COLDBOLT, "COLDBOLT", "Cold_Bolt" } ,
 { MG_ENERGYCOAT, "ENERGYCOAT", "Energy_Coat" } ,
 { MG_FIREBALL, "FIREBALL", "Fire_Ball" } ,
 { MG_FIREBOLT, "FIREBOLT", "Fire_Bolt" } ,
 { MG_FIREWALL, "FIREWALL", "Fire_Wall" } ,
 { MG_FROSTDIVER, "FROSTDIVER", "Frost_Diver" } ,
 { MG_LIGHTNINGBOLT, "LIGHTNINGBOLT", "Lightening_Bolt" } ,
 { MG_NAPALMBEAT, "NAPALMBEAT", "Napalm_Beat" } ,
 { MG_SAFETYWALL, "SAFETYWALL", "Safety_Wall" } ,
 { MG_SIGHT, "SIGHT", "Sight" } ,
 { MG_SOULSTRIKE, "SOULSTRIKE", "Soul_Strike" } ,
 { MG_SRECOVERY, "SRECOVERY", "Increase_SP_Recovery" } ,
 { MG_STONECURSE, "STONECURSE", "Stone_Curse" } ,
 { MG_THUNDERSTORM, "THUNDERSTORM", "Thunderstorm" } ,
 { MO_ABSORBSPIRITS, "ABSORBSPIRITS", "Spiritual_Sphere_Absorption" } ,
 { MO_BLADESTOP, "BLADESTOP", "Blade_Stop" } ,
 { MO_BODYRELOCATION, "BODYRELOCATION", "Snap" } ,
 { MO_CALLSPIRITS, "CALLSPIRITS", "Summon_Spirit_Sphere" } ,
 { MO_CHAINCOMBO, "CHAINCOMBO", "Raging_Quadruple_Blow" } ,
 { MO_COMBOFINISH, "COMBOFINISH", "Raging_Thrust" } ,
 { MO_DODGE, "DODGE", "Flee" } ,
 { MO_EXPLOSIONSPIRITS, "EXPLOSIONSPIRITS", "Fury" } ,
 { MO_EXTREMITYFIST, "EXTREMITYFIST", "Guillotine_Fist" } ,
 { MO_FINGEROFFENSIVE, "FINGEROFFENSIVE", "Throw_Spirit_Sphere" } ,
 { MO_INVESTIGATE, "INVESTIGATE", "Occult_Impaction" } ,
 { MO_IRONHAND, "IRONHAND", "Iron_Fists" } ,
 { MO_SPIRITSRECOVERY, "SPIRITSRECOVERY", "Spiritual_Cadence" } ,
 { MO_STEELBODY, "STEELBODY", "Mental_Strength" } ,
 { MO_TRIPLEATTACK, "TRIPLEATTACK", "Raging_Trifecta_Blow" } ,
 { NPC_ATTRICHANGE, "ATTRICHANGE", "NPC_ATTRICHANGE" } ,
 { NPC_BARRIER, "BARRIER", "NPC_BARRIER" } ,
 { NPC_BLINDATTACK, "BLINDATTACK", "NPC_BLINDATTACK" } ,
 { NPC_BLOODDRAIN, "BLOODDRAIN", "NPC_BLOODDRAIN" } ,
 { NPC_CHANGEDARKNESS, "CHANGEDARKNESS", "NPC_CHANGEDARKNESS" } ,
 { NPC_CHANGEFIRE, "CHANGEFIRE", "NPC_CHANGEFIRE" } ,
 { NPC_CHANGEGROUND, "CHANGEGROUND", "NPC_CHANGEGROUND" } ,
 { NPC_CHANGEHOLY, "CHANGEHOLY", "NPC_CHANGEHOLY" } ,
 { NPC_CHANGEPOISON, "CHANGEPOISON", "NPC_CHANGEPOISON" } ,
 { NPC_CHANGETELEKINESIS, "CHANGETELEKINESIS", "NPC_CHANGETELEKINESIS" } ,
 { NPC_CHANGEWATER, "CHANGEWATER", "NPC_CHANGEWATER" } ,
 { NPC_CHANGEWIND, "CHANGEWIND", "NPC_CHANGEWIND" } ,
 { NPC_COMBOATTACK, "COMBOATTACK", "NPC_COMBOATTACK" } ,
 { NPC_CRITICALSLASH, "CRITICALSLASH", "NPC_CRITICALSLASH" } ,
 { NPC_CURSEATTACK, "CURSEATTACK", "NPC_CURSEATTACK" } ,
 { NPC_DARKBLESSING, "DARKBLESSING", "NPC_DARKBLESSING" } ,
 { NPC_DARKBREATH, "DARKBREATH", "NPC_DARKBREATH" } ,
 { NPC_DARKCROSS, "DARKCROSS", "NPC_DARKCROSS" } ,
 { NPC_DARKNESSATTACK, "DARKNESSATTACK", "NPC_DARKNESSATTACK" } ,
 { NPC_DEFENDER, "DEFENDER", "NPC_DEFENDER" } ,
 { NPC_EMOTION, "EMOTION", "NPC_EMOTION" } ,
 { NPC_EMOTION_ON, "EMOTION_ON", "NPC_EMOTION_ON" } ,
 { NPC_ENERGYDRAIN, "ENERGYDRAIN", "NPC_ENERGYDRAIN" } ,
 { NPC_FIREATTACK, "FIREATTACK", "NPC_FIREATTACK" } ,
 { NPC_GROUNDATTACK, "GROUNDATTACK", "NPC_GROUNDATTACK" } ,
 { NPC_GUIDEDATTACK, "GUIDEDATTACK", "NPC_GUIDEDATTACK" } ,
 { NPC_HALLUCINATION, "HALLUCINATION", "NPC_HALLUCINATION" } ,
 { NPC_HOLYATTACK, "HOLYATTACK", "NPC_HOLYATTACK" } ,
 { NPC_KEEPING, "KEEPING", "NPC_KEEPING" } ,
 { NPC_LICK, "LICK", "NPC_LICK" } ,
 { NPC_MAGICALATTACK, "MAGICALATTACK", "NPC_MAGICALATTACK" } ,
 { NPC_MENTALBREAKER, "MENTALBREAKER", "NPC_MENTALBREAKER" } ,
 { NPC_METAMORPHOSIS, "METAMORPHOSIS", "NPC_METAMORPHOSIS" } ,
 { NPC_PETRIFYATTACK, "PETRIFYATTACK", "NPC_PETRIFYATTACK" } ,
 { NPC_PIERCINGATT, "PIERCINGATT", "NPC_PIERCINGATT" } ,
 { NPC_POISON, "POISON", "NPC_POISON" } ,
 { NPC_POISONATTACK, "POISONATTACK", "NPC_POISONATTACK" } ,
 { NPC_PROVOCATION, "PROVOCATION", "NPC_PROVOCATION" } ,
 { NPC_RANDOMATTACK, "RANDOMATTACK", "NPC_RANDOMATTACK" } ,
 { NPC_RANGEATTACK, "RANGEATTACK", "NPC_RANGEATTACK" } ,
 { NPC_REBIRTH, "REBIRTH", "NPC_REBIRTH" } ,
 { NPC_SELFDESTRUCTION, "SELFDESTRUCTION", "Kabooooom!" } ,
 { NPC_SILENCEATTACK, "SILENCEATTACK", "NPC_SILENCEATTACK" } ,
 { NPC_SLEEPATTACK, "SLEEPATTACK", "NPC_SLEEPATTACK" } ,
 { NPC_SMOKING, "SMOKING", "NPC_SMOKING" } ,
 { NPC_SPLASHATTACK, "SPLASHATTACK", "NPC_SPLASHATTACK" } ,
 { NPC_STUNATTACK, "STUNATTACK", "NPC_STUNATTACK" } ,
 { NPC_SUICIDE, "SUICIDE", "NPC_SUICIDE" } ,
 { NPC_SUMMONMONSTER, "SUMMONMONSTER", "NPC_SUMMONMONSTER" } ,
 { NPC_SUMMONSLAVE, "SUMMONSLAVE", "NPC_SUMMONSLAVE" } ,
 { NPC_TELEKINESISATTACK, "TELEKINESISATTACK", "NPC_TELEKINESISATTACK" } ,
 { NPC_TRANSFORMATION, "TRANSFORMATION", "NPC_TRANSFORMATION" } ,
 { NPC_WATERATTACK, "WATERATTACK", "NPC_WATERATTACK" } ,
 { NPC_WINDATTACK, "WINDATTACK", "NPC_WINDATTACK" } ,
 { NV_BASIC, "BASIC", "Basic_Skill" } ,
 { NV_FIRSTAID, "FIRSTAID", "First Aid" } ,
 { NV_TRICKDEAD, "TRICKDEAD", "Play_Dead" } ,
 { PA_GOSPEL, "GOSPEL", "Battle_Chant" } ,
 { PA_PRESSURE, "PRESSURE", "Gloria_Domini" } ,
 { PA_SACRIFICE, "SACRIFICE", "Martyr's_Reckoning" } ,
 { PA_SHIELDCHAIN, "SHIELDCHAIN", "Shield_Chain" } ,
 { PF_DOUBLECASTING, "DOUBLECASTING", "Double_Casting" } ,
 { PF_FOGWALL, "FOGWALL", "Blinding_Mist" } ,
 { PF_HPCONVERSION, "HPCONVERSION", "Indulge" } ,
 { PF_MEMORIZE, "MEMORIZE", "Foresight" } ,
 { PF_MINDBREAKER, "MINDBREAKER", "Mind_Breaker" } ,
 { PF_SOULBURN, "SOULBURN", "Soul_Siphon" } ,
 { PF_SOULCHANGE, "SOULCHANGE", "Soul_Exhale" } ,
 { PF_SPIDERWEB, "SPIDERWEB", "Fiber_Lock" } ,
 { PR_ASPERSIO, "ASPERSIO", "Aspersio" } ,
 { PR_BENEDICTIO, "BENEDICTIO", "B.S_Sacramenti" } ,
 { PR_GLORIA, "GLORIA", "Gloria" } ,
 { PR_IMPOSITIO, "IMPOSITIO", "Impositio_Manus" } ,
 { PR_KYRIE, "KYRIE", "Kyrie_Eleison" } ,
 { PR_LEXAETERNA, "LEXAETERNA", "Lex_Aeterna" } ,
 { PR_LEXDIVINA, "LEXDIVINA", "Lex_Divina" } ,
 { PR_MACEMASTERY, "MACEMASTERY", "Mace_Mastery" } ,
 { PR_MAGNIFICAT, "MAGNIFICAT", "Magnificat" } ,
 { PR_MAGNUS, "MAGNUS", "Magnus_Exorcismus" } ,
 { PR_SANCTUARY, "SANCTUARY", "Sanctuary" } ,
 { PR_SLOWPOISON, "SLOWPOISON", "Slow_Poison" } ,
 { PR_STRECOVERY, "STRECOVERY", "Status_Recovery" } ,
 { PR_SUFFRAGIUM, "SUFFRAGIUM", "Suffragium" } ,
 { PR_TURNUNDEAD, "TURNUNDEAD", "Turn_Undead" } ,
 { RG_BACKSTAP, "BACKSTAP", "Back_Stab" } ,
 { RG_CLEANER, "CLEANER", "Remover" } ,
 { RG_COMPULSION, "COMPULSION", "Haggle" } ,
 { RG_FLAGGRAFFITI, "FLAGGRAFFITI", "Piece" } ,
 { RG_GANGSTER, "GANGSTER", "Slyness" } ,
 { RG_GRAFFITI, "GRAFFITI", "Scribble" } ,
 { RG_INTIMIDATE, "INTIMIDATE", "Snatch" } ,
 { RG_PLAGIARISM, "PLAGIARISM", "Intimidate" } ,
 { RG_RAID, "RAID", "Sightless_Mind" } ,
 { RG_SNATCHER, "SNATCHER", "Gank" } ,
 { RG_STEALCOIN, "STEALCOIN", "Mug" } ,
 { RG_STRIPARMOR, "STRIPARMOR", "Divest_Armor" } ,
 { RG_STRIPHELM, "STRIPHELM", "Divest_Helm" } ,
 { RG_STRIPSHIELD, "STRIPSHIELD", "Divest_Shield" } ,
 { RG_STRIPWEAPON, "STRIPWEAPON", "Divest_Weapon" } ,
 { RG_TUNNELDRIVE, "TUNNELDRIVE", "Stalk" } ,
 { SA_ABRACADABRA, "ABRACADABRA", "Hocus-pocus" } ,
 { SA_ADVANCEDBOOK, "ADVANCEDBOOK", "Advanced_Book" } ,
 { SA_AUTOSPELL, "AUTOSPELL", "Hindsight" } ,
 { SA_CASTCANCEL, "CASTCANCEL", "Cast_Cancel" } ,
 { SA_CLASSCHANGE, "CLASSCHANGE", "Class_Change" } ,
 { SA_COMA, "COMA", "Coma" } ,
 { SA_DEATH, "DEATH", "Grim_Reaper" } ,
 { SA_DELUGE, "DELUGE", "Deluge" } ,
 { SA_DISPELL, "DISPELL", "Dispell" } ,
 { SA_DRAGONOLOGY, "DRAGONOLOGY", "Dragonology" } ,
 { SA_FLAMELAUNCHER, "FLAMELAUNCHER", "Endow_Blaze" } ,
 { SA_FORTUNE, "FORTUNE", "Gold_Digger" } ,
 { SA_FREECAST, "FREECAST", "Free_Cast" } ,
 { SA_FROSTWEAPON, "FROSTWEAPON", "Endow_Tsunami" } ,
 { SA_FULLRECOVERY, "FULLRECOVERY", "Rejuvenation" } ,
 { SA_GRAVITY, "GRAVITY", "Gravity" } ,
 { SA_INSTANTDEATH, "INSTANTDEATH", "Suicide" } ,
 { SA_LANDPROTECTOR, "LANDPROTECTOR", "Magnetic_Earth" } ,
 { SA_LEVELUP, "LEVELUP", "Leveling" } ,
 { SA_LIGHTNINGLOADER, "LIGHTNINGLOADER", "Endow_Tornado" } ,
 { SA_MAGICROD, "MAGICROD", "Magic_Rod" } ,
 { SA_MONOCELL, "MONOCELL", "Mono_Cell" } ,
 { SA_QUESTION, "QUESTION", "Questioning" } ,
 { SA_REVERSEORCISH, "REVERSEORCISH", "Grampus_Morph" } ,
 { SA_SEISMICWEAPON, "SEISMICWEAPON", "Endow_Quake" } ,
 { SA_SPELLBREAKER, "SPELLBREAKER", "Spell_Breaker" } ,
 { SA_SUMMONMONSTER, "SUMMONMONSTER", "Monster_Chant" } ,
 { SA_TAMINGMONSTER, "TAMINGMONSTER", "Beastly_Hypnosis" } ,
 { SA_VIOLENTGALE, "VIOLENTGALE", "Whirlwind" } ,
 { SA_VOLCANO, "VOLCANO", "Volcano" } ,
 { SG_DEVIL, "DEVIL", "Devil_of_the_Sun,_Moon_and_Stars" } ,
 { SG_FEEL, "FEEL", "Feeling_of_the_Sun,_Moon_and_Star" } ,
 { SG_FRIEND, "FRIEND", "Companion_of_the_Sun_and_Moon" } ,
 { SG_FUSION, "FUSION", "Union_of_the_Sun,_Moon_and_Stars" } ,
 { SG_HATE, "HATE", "Hatred_of_the_Sun,_Moon_and_Stars" } ,
 { SG_KNOWLEDGE, "KNOWLEDGE", "Knowledge_of_the_Sun,_Moon_and_Stars" } ,
 { SG_MOON_ANGER, "ANGER", "Fury_of_the_Moon" } ,
 { SG_MOON_BLESS, "BLESS", "Bless_of_the_Moon" } ,
 { SG_MOON_COMFORT, "COMFORT", "Comfort_of_the_Moon" } ,
 { SG_MOON_WARM, "WARM", "Warmth_of_the_Moon" } ,
 { SG_STAR_ANGER, "ANGER", "Fury_of_the_Stars" } ,
 { SG_STAR_BLESS, "BLESS", "Bless_of_the_Stars" } ,
 { SG_STAR_COMFORT, "COMFORT", "Comfort_of_the_Stars" } ,
 { SG_STAR_WARM, "WARM", "Warmth_of_the_Stars" } ,
 { SG_SUN_ANGER, "ANGER", "Fury_of_the_Sun" } ,
 { SG_SUN_BLESS, "BLESS", "Bless_of_the_Sun" } ,
 { SG_SUN_COMFORT, "COMFORT", "Comfort_of_the_Sun" } ,
 { SG_SUN_WARM, "WARM", "Warmth_of_the_Sun" } ,
 { SL_ALCHEMIST, "ALCHEMIST", "Spirit_of_Alchemist" } ,
 { SL_ASSASIN, "ASSASIN", "Spirit_of_Assassin" } ,
 { SL_BARDDANCER, "BARDDANCER", "Spirit_of_Bard_and_Dancer" } ,
 { SL_BLACKSMITH, "BLACKSMITH", "Spirit_of_Blacksmith" } ,
 { SL_CRUSADER, "CRUSADER", "Spirit_of_Crusader" } ,
 { SL_HUNTER, "HUNTER", "Spirit_of_Hunter" } ,
 { SL_KAAHI, "KAAHI", "Kaahi" } ,
 { SL_KAINA, "KAINA", "Kaina" } ,
 { SL_KAITE, "KAITE", "Kaite" } ,
 { SL_KAIZEL, "KAIZEL", "Kaizel" } ,
 { SL_KAUPE, "KAUPE", "Kaupe" } ,
 { SL_KNIGHT, "KNIGHT", "Spirit_of_Knight" } ,
 { SL_MONK, "MONK", "Spirit_of_Monk" } ,
 { SL_PRIEST, "PRIEST", "Spirit_of_Priest" } ,
 { SL_ROGUE, "ROGUE", "Spirit_of_Rogue" } ,
 { SL_SAGE, "SAGE", "Spirit_of_Sage" } ,
 { SL_SKA, "SKA", "Eska" } ,
 { SL_SKE, "SKE", "Eske" } ,
 { SL_SMA, "SMA", "Esma" } ,
 { SL_SOULLINKER, "SOULLINKER", "Spirit_of_Soul_Linker" } ,
 { SL_STAR, "STAR", "Spirit_of_Stars" } ,
 { SL_STIN, "STIN", "Estin" } ,
 { SL_STUN, "STUN", "Estun" } ,
 { SL_SUPERNOVICE, "SUPERNOVICE", "Spirit_of_Super_Novice" } ,
 { SL_SWOO, "SWOO", "Eswoo" } ,
 { SL_WIZARD, "WIZARD", "Spirit_of_Wizard" } ,
 { SM_AUTOBERSERK, "AUTOBERSERK", "Berserk" } ,
 { SM_BASH, "BASH", "Bash" } ,
 { SM_ENDURE, "ENDURE", "Endure" } ,
 { SM_FATALBLOW, "FATALBLOW", "Fatal_Blow" } ,
 { SM_MAGNUM, "MAGNUM", "Magnum_Break" } ,
 { SM_MOVINGRECOVERY, "MOVINGRECOVERY", "HP_Recovery_While_Moving" } ,
 { SM_PROVOKE, "PROVOKE", "Provoke" } ,
 { SM_RECOVERY, "RECOVERY", "Increase_HP_Recovery" } ,
 { SM_SWORD, "SWORD", "Sword_Mastery" } ,
 { SM_TWOHAND, "TWOHAND", "Two-Handed_Sword_Mastery" } ,
 { SN_FALCONASSAULT, "FALCONASSAULT", "Falcon_Assault" } ,
 { SN_SHARPSHOOTING, "SHARPSHOOTING", "Focused_Arrow_Strike" } ,
 { SN_SIGHT, "SIGHT", "Falcon_Eyes" } ,
 { SN_WINDWALK, "WINDWALK", "Wind_Walker" } ,
 { ST_CHASEWALK, "CHASEWALK", "Stealth" } ,
 { ST_REJECTSWORD, "REJECTSWORD", "Counter_Instinct" } ,
 { ST_STEALBACKPACK, "STEALBACKPACK", "Pickpocket" } ,
 { ST_PRESERVE, "PRESERVE", "Preserve" } ,
 { ST_FULLSTRIP, "FULLSTRIP", "Full_Divestment" } ,
 { TF_BACKSLIDING, "BACKSLIDING", "Back_Slide" } ,
 { TF_DETOXIFY, "DETOXIFY", "Detoxify" } ,
 { TF_DOUBLE, "DOUBLE", "Double_Attack" } ,
 { TF_HIDING, "HIDING", "Hiding" } ,
 { TF_MISS, "MISS", "Improve_Dodge" } ,
 { TF_PICKSTONE, "PICKSTONE", "Find_Stone" } ,
 { TF_POISON, "POISON", "Envenom" } ,
 { TF_SPRINKLESAND, "SPRINKLESAND", "Sand_Attack" } ,
 { TF_STEAL, "STEAL", "Steal" } ,
 { TF_THROWSTONE, "THROWSTONE", "Stone_Fling" } ,
 { TK_COUNTER, "COUNTER", "Counter" } ,
 { TK_DODGE, "DODGE", "Dodge" } ,
 { TK_DOWNKICK, "DOWNKICK", "Down_Kick" } ,
 { TK_HIGHJUMP, "HIGHJUMP", "High_Jump" } ,
 { TK_HPTIME, "HPTIME", "HP_Time" } ,
 { TK_JUMPKICK, "JUMPKICK", "Jump_Kick" } ,
 { TK_POWER, "POWER", "Power" } ,
 { TK_READYCOUNTER, "READYCOUNTER", "Ready_Counter" } ,
 { TK_READYDOWN, "READYDOWN", "Ready_Down" } ,
 { TK_READYSTORM, "READYSTORM", "Ready_Storm" } ,
 { TK_READYTURN, "READYTURN", "Ready_Turn" } ,
 { TK_RUN, "RUN", "Run" } ,
 { TK_SEVENWIND, "SEVENWIND", "Seven_Wind" } ,
 { TK_SPTIME, "SPTIME", "SP_Time" } ,
 { TK_STORMKICK, "STORMKICK", "Storm_Kick" } ,
 { TK_TURNKICK, "TURNKICK", "Turn_Kick" } ,
 { WE_BABY, "BABY", "Mom,_Dad,_I_love_you!" } ,
 { WE_CALLBABY, "CALLBABY", "Come_to_me,_honey~" } ,
 { WE_CALLPARENT, "CALLPARENT", "Mom,_Dad,_I_miss_you!" } ,
 { WE_CALLPARTNER, "CALLPARTNER", "Romantic_Rendezvous" } ,
 { WE_FEMALE, "FEMALE", "Loving_Touch" } ,
 { WE_MALE, "MALE", "Undying_Love" } ,
 { WS_CARTBOOST, "CARTBOOST", "Cart_Boost" } ,
 { WS_CARTTERMINATION, "CARTTERMINATION", "Cart_Termination" } ,
 { WS_CREATECOIN, "CREATECOIN", "Coin_Craft" } ,
 { WS_CREATENUGGET, "CREATENUGGET", "Nugget_Craft" } ,
 { WS_MELTDOWN, "MELTDOWN", "Shattering_Strike" } ,
 { WS_OVERTHRUSTMAX, "OVERTHRUSTMAX", "Max_Power-Thust" } ,
 { WS_SYSTEMCREATE, "SYSTEMCREATE", "Auto_Attacking_Machine_Craft" } ,
 { WS_WEAPONREFINE, "WEAPONREFINE", "Weapon_Refine" } ,
 { WZ_EARTHSPIKE, "EARTHSPIKE", "Earth_Spike" } ,
 { WZ_ESTIMATION, "ESTIMATION", "Sense" } ,
 { WZ_FIREIVY, "FIREIVY", "Fire_Ivy" } ,
 { WZ_FIREPILLAR, "FIREPILLAR", "Fire_Pillar" } ,
 { WZ_FROSTNOVA, "FROSTNOVA", "Frost_Nova" } ,
 { WZ_HEAVENDRIVE, "HEAVENDRIVE", "Heaven's_Drive" } ,
 { WZ_ICEWALL, "ICEWALL", "Ice_Wall" } ,
 { WZ_JUPITEL, "JUPITEL", "Jupitel_Thunder" } ,
 { WZ_METEOR, "METEOR", "Meteor_Storm" } ,
 { WZ_QUAGMIRE, "QUAGMIRE", "Quagmire" } ,
 { WZ_SIGHTRASHER, "SIGHTRASHER", "Sightrasher" } ,
 { WZ_STORMGUST, "STORMGUST", "Storm_Gust" } ,
 { WZ_VERMILION, "VERMILION", "Lord_of_Vermilion" } ,
 { WZ_WATERBALL, "WATERBALL", "Water_Ball" } ,
 { 0, 0, 0 }
};

static const char dirx[8] = { 0, 1, 1, 1, 0,-1,-1,-1};
static const char diry[8] = { 1, 1, 0,-1,-1,-1, 0, 1};

static int rdamage;

// �X�L���f?�^�x?�X 
struct skill_db skill_db[MAX_SKILL_DB];

// �A�C�e���쐬�f?�^�x?�X 
struct skill_produce_db skill_produce_db[MAX_SKILL_PRODUCE_DB];

// ��쐬�X�L���f?�^�x?�X 
struct skill_arrow_db skill_arrow_db[MAX_SKILL_ARROW_DB];

// �A�u���J�_�u��?���X�L���f?�^�x?�X 
struct skill_abra_db skill_abra_db[MAX_SKILL_ABRA_DB];

// macros to check for out of bounds errors [celest]
// i: Skill ID, l: Skill Level, var: Value to return after checking
// for values that don't require level just put a one (putting 0 will trigger return 0; instead
// for values that might need to use a different function just skill_chk would suffice.
#define skill_chk(i, l) if(i >= 10000 && i < 10015) {i -= 9500;} if(i < 1 || i > MAX_SKILL_DB) {return 0;} if(l <= 0 || l > MAX_SKILL_LEVEL) {return 0;}
#define skill_get(var, i, l)	{ skill_chk(i, l); return var; }

// Skill DB
int	skill_get_hit( int id ){ skill_get (skill_db[id].hit, id, 1); }
int	skill_get_inf( int id ){ skill_chk (id, 1); return (id < 500) ? skill_db[id].inf : guild_skill_get_inf(id); }
int	skill_get_pl( int id ){ skill_get (skill_db[id].pl, id, 1); }
int	skill_get_nk( int id ){ skill_get (skill_db[id].nk, id, 1); }
int skill_get_max( int id ){ skill_chk (id, 1); return (id < 500) ? skill_db[id].max : guild_skill_get_max(id); }
int skill_get_range( int id , int lv ){ skill_chk (id, lv); return (id < 500) ? skill_db[id].range[lv-1] : 0; }
int	skill_get_hp( int id ,int lv ){ skill_get (skill_db[id].hp[lv-1], id, lv); }
int	skill_get_sp( int id ,int lv ){ skill_get (skill_db[id].sp[lv-1], id, lv); }
int	skill_get_zeny( int id ,int lv ){ skill_get (skill_db[id].zeny[lv-1], id, lv); }
int	skill_get_num( int id ,int lv ){ skill_get (skill_db[id].num[lv-1], id, lv); }
int	skill_get_cast( int id ,int lv ){ skill_get (skill_db[id].cast[lv-1], id, lv); }
int	skill_get_delay( int id ,int lv ){ skill_get (skill_db[id].delay[lv-1], id, lv); }
int	skill_get_time( int id ,int lv ){ skill_get (skill_db[id].upkeep_time[lv-1], id, lv); }
int	skill_get_time2( int id ,int lv ){ skill_get (skill_db[id].upkeep_time2[lv-1], id, lv); }
int	skill_get_castdef( int id ){ skill_get (skill_db[id].cast_def_rate, id, 1); }
int	skill_get_weapontype( int id ){ skill_get (skill_db[id].weapon, id, 1); }
int	skill_get_inf2( int id ){ skill_get (skill_db[id].inf2, id, 1); }
int	skill_get_castcancel( int id ){ skill_get (skill_db[id].castcancel, id, 1); }
int	skill_get_maxcount( int id ){ skill_get (skill_db[id].maxcount, id, 1); }
int	skill_get_blewcount( int id ,int lv ){ skill_get (skill_db[id].blewcount[lv-1], id, lv); }
int	skill_get_mhp( int id ,int lv ){ skill_get (skill_db[id].mhp[lv-1], id, lv); }
int	skill_get_castnodex( int id ,int lv ){ skill_get (skill_db[id].castnodex[lv-1], id, lv); }
int	skill_get_delaynodex( int id ,int lv ){ skill_get (skill_db[id].delaynodex[lv-1], id, lv); }
int	skill_get_nocast ( int id ){ skill_get (skill_db[id].nocast, id, 1); }
int	skill_get_type( int id ){ skill_get (skill_db[id].skill_type, id, 1); }
int	skill_get_unit_id ( int id, int flag ){ skill_get (skill_db[id].unit_id[flag], id, 1); }
int	skill_get_unit_layout_type( int id ,int lv ){ skill_get (skill_db[id].unit_layout_type[lv-1], id, lv); }
int	skill_get_unit_interval( int id ){ skill_get (skill_db[id].unit_interval, id, 1); }
int	skill_get_unit_range( int id ){ skill_get (skill_db[id].unit_range, id, 1); }
int	skill_get_unit_target( int id ){ skill_get (skill_db[id].unit_target, id, 1); }
int	skill_get_unit_flag( int id ){ skill_get (skill_db[id].unit_flag, id, 1); }
const char*	skill_get_name( int id )
{ 
	if (id >= 10000 && id < 10015) id -= 9500;
	if (id < 1 || id > MAX_SKILL_DB) return "UNKNOWN_SKILL"; //Can't use skill_chk because we return a string.
	return skill_db[id].name; 
}

// �v���g�^�C�v 
int skill_check_condition( map_session_data *sd,int type);
int skill_castend_damage_id( block_list* src, block_list *bl,unsigned short skillid,unsigned short skilllv,unsigned long tick,int flag );

int skill_clear_element_field(block_list *bl);

struct skill_unit_group_tickset *skill_unitgrouptickset_search(block_list *bl,struct skill_unit_group *sg,unsigned long tick);
int skill_unit_onout(struct skill_unit *src,block_list *bl,unsigned long tick);
int skill_unit_onplace(struct skill_unit *src,block_list *bl,unsigned long tick);
int skill_unit_onplace_timer(struct skill_unit *src,block_list *bl,unsigned long tick);
int skill_castend_delay(block_list& src, block_list &bl, unsigned short skillid, unsigned short skilllv, unsigned long tick, int flag);

int enchant_eff[5] = { 10, 14, 17, 19, 20 };
int deluge_eff[5] = { 5, 9, 12, 14, 15 };





// for graffiti cleaner [Valaris]
class CSkillGraffitiRemover : public CMapProcessor
{
public:
	CSkillGraffitiRemover()	{}
	~CSkillGraffitiRemover()	{}
	virtual int process(block_list& bl) const
	{
		struct skill_unit *unit = bl.get_sk();
		if( unit && unit->group && unit->group->unit_id == 0xb0 )
			skill_delunit(unit);

		return 0;
	}
};
/*==========================================
 * �����h�v���e�N�^?�`�F�b�N(foreachinarea)
 *------------------------------------------
 */
class CSkillLandprotector : public CMapProcessor
{
	unsigned short skillid;
public:
	mutable int& alive;
	CSkillLandprotector(unsigned short sid, int& a) : skillid(sid),alive(a)	{}
	~CSkillLandprotector()	{}
	virtual int process(block_list& bl) const
	{
		struct skill_unit &unit = (struct skill_unit &)bl;
		if( skillid == SA_LANDPROTECTOR || skillid == HW_GANBANTEIN )
			skill_delunit(&unit);
		else if (unit.group && unit.group->skill_id == SA_LANDPROTECTOR)
			alive = 0;
		return 0;
	}
};
/*==========================================
 * variation of skill_landprotector
 *------------------------------------------
 */
class CSkillGanbatein : public CMapProcessor
{
public:
	CSkillGanbatein()	{}
	~CSkillGanbatein()	{}
	virtual int process(block_list& bl) const
	{
		struct skill_unit &unit = (struct skill_unit &)bl;
		if( unit.group )
		{
			if( unit.group->skill_id == SA_LANDPROTECTOR)
				skill_delunit(&unit);
			else
				skill_delunitgroup(*unit.group);
		}
		return 0;
	}
};
/*==========================================
 * �C�h�D���̗ь�̉�?��(foreachinarea)
 *------------------------------------------
 */
class CSkillIdunheal : public CMapProcessor
{
	ICL_EMPTY_COPYCONSTRUCTOR(CSkillIdunheal)
	struct skill_unit& unit;
public:
	CSkillIdunheal(struct skill_unit& u) : unit(u)	{}
	~CSkillIdunheal()	{}
	virtual int process(block_list& bl) const
	{
		struct skill_unit_group *sg = unit.group;
		nullpo_retr(0, sg);

		if( bl != BL_PC && bl != BL_MOB )
			return 0;
		if( bl.id != sg->src_id )
		{
			int heal = 30 + sg->skill_lv * 5 + ((sg->val1) >> 16) * 5 + ((sg->val2) & 0xfff) / 2;
			clif_skill_nodamage(unit, bl, AL_HEAL, heal, 1);
			battle_heal(NULL, &bl, heal, 0, 0);
		}
		return 0;
	}
};
/*==========================================
 * �w���??��src��?���ėL?�ȃ^?�Q�b�g��bl��?��?����(foreachinarea)
 *------------------------------------------
 */
class CSkillCounttarget : public CMapProcessor
{
	ICL_EMPTY_COPYCONSTRUCTOR(CSkillCounttarget)
	block_list& src;
public:
	CSkillCounttarget(block_list& s) : src(s)	{}
	~CSkillCounttarget()	{}
	virtual int process(block_list& bl) const
	{
		if( battle_check_target(&src,&bl,BCT_ENEMY) > 0 )
			return 1;
		return 0;
	}
};
/*==========================================
 * �g���b�v��??��(foreachinarea)
 *------------------------------------------
 */
class CSkillTrapsplash : public CMapProcessor
{
	struct skill_unit &unit;
	unsigned long tick;
	int splash_count;

public:
	CSkillTrapsplash(struct skill_unit &u, unsigned long t, int sc)
		: unit(u), tick(t), splash_count(sc)
	{}
	~CSkillTrapsplash()	{}
	virtual int process(block_list& bl) const
	{
		int i;
		struct skill_unit_group *sg= unit.group;
		nullpo_retr(0, sg );
		block_list *ss= block_list::from_blid(sg->src_id);
		nullpo_retr(0, ss );

		if(battle_check_target(&unit,&bl,BCT_ENEMY) > 0)
		{
			switch(sg->unit_id)
			{
				case UNT_SANDMAN:	// �T���h�}�� 
				case UNT_FLASHER:	// �t���b�V��? 
				case UNT_SHOCKWAVE:	// �V���b�N�E�F?�u�g���b�v 
					skill_additional_effect(ss,&bl,sg->skill_id,sg->skill_lv,BF_MISC,tick);
					break;
				case UNT_BLASTMINE:	// �u���X�g�}�C�� 
				case UNT_CLAYMORETRAP:	// �N���C���A?�g���b�v 
					for(i=0;i<splash_count;++i){
						skill_attack(BF_MISC,ss,&unit,&bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
					}
					break;
				case UNT_FREEZINGTRAP:	// �t��?�W���O�g���b�v 
						skill_attack(BF_WEAPON,	ss,&unit,&bl,sg->skill_id,sg->skill_lv,tick,(sg->val2)?0x0500:0);
					break;
				default:
					break;
			}
		}
		return 0;
	}
};
/*==========================================
 *
 *------------------------------------------
 */
class CSkillAttackArea : public CMapProcessor
{
	int atk_type;
	block_list& src;
	block_list& dsrc;
	int skillid;
	int skilllv;
	unsigned long tick;
	int flag;
	int type;
public:
	CSkillAttackArea(int at, block_list& s, block_list& d,
		int sid, int slv, unsigned long t, int f, int ty)
		: atk_type(at), src(s), dsrc(d), 
		skillid(sid), skilllv(slv), tick(t), flag(f), type(ty)
	{  }
	~CSkillAttackArea()
	{  }

	virtual int process(block_list& bl) const
	{
		if( skillid>0 && skilllv<=0) return 0;	// celest

		if( battle_check_target(&dsrc,&bl,type) > 0 )
			skill_attack(atk_type,&src,&dsrc,&bl,skillid,skilllv,tick,flag);
		return 0;
	}
};

/*==========================================
 * �����W��?�N?�X�N��?������?��(foreachinarea)
 *------------------------------------------
 */
class CSkillFrostjoke : public CMapProcessor
{
	block_list &src;
	unsigned short skillid;
	unsigned short skilllv;
	unsigned long tick;
public:
	CSkillFrostjoke(block_list &s, unsigned short sid, unsigned short slv, unsigned long t)
		:	src(s),skillid(sid),skilllv(slv),tick(t)
	{}
	~CSkillFrostjoke()	{}
	virtual int process(block_list& bl) const
	{
		if( src.id == bl.id ||	//�����ɂ�?���Ȃ�
			!bl.is_on_map() ||
			bl.is_dead() )
			return 0;

		// don't hit hidden gm's
		map_session_data *sd = bl.get_sd();
		if (sd && (sd->status.option & OPTION_HIDE) && sd->isGM() )
			return 0;

		//It has been reported that Scream/Joke works the same regardless of woe-setting. [Skotlex]
//		if (maps[src.m].flag.gvg || maps[src.m].flag.pvp)
//		{	// we freeze everybody except of ourselfes on pvp/gvg [veider]
//			skill_additional_effect(&src,&bl,skillid,skilllv,BF_MISC,tick);
//		}
//		else
//		{	
			if(battle_check_target(&src,&bl,BCT_ENEMY) > 0)
				skill_additional_effect(&src,&bl,skillid,skilllv,BF_MISC,tick);
			else if(battle_check_target(&src,&bl,BCT_PARTY) > 0 && rand()%100 < 10)
				skill_additional_effect(&src,&bl,skillid,skilllv,BF_MISC,tick);
//		}
//		// so on non-pvp/gvg we are just freezing as freezed before
		return 0;
	}
};

/*==========================================
 * �X�L�����j�b�g���ʔ���/���E����(foreachinarea)
 *    bl: ���j�b�g(BL_PC/BL_MOB)
 *------------------------------------------
 */
class CSkillUnitEffect : public CMapProcessor, public basics::Mutex
{
	struct skill_unit &unit;
	unsigned long tick;
	int flag;
public:
	CSkillUnitEffect(struct skill_unit &u, unsigned long t,  int f)
		: unit(u), tick(t), flag(f)
	{}
	~CSkillUnitEffect()	{}
	virtual int process(block_list& bl) const
	{
		struct skill_unit_group *group=unit.group;
		nullpo_retr(0, group);

		if (bl!=BL_PC && bl!=BL_MOB)
			return 0;

		if (!unit.alive || !bl.is_on_map() )
			return 0;

		if (flag)
			skill_unit_onplace(&unit,&bl,tick);
		else
		{	// threadsafe the static
			basics::ScopeLock sl(*this);
			static bool called=false;
			skill_unit_onout(&unit,&bl,tick);
			skill_unit *punit = block_list::skillunit_oncell(bl,bl.x,bl.y,group->skill_id,&unit);
			if(punit && !called)
			{
				called = true;
				skill_unit_onplace(punit,&bl,tick);
				called = false;
			}
		}
		return 0;
	}
};






/*==========================================
 * ��??�L�������݊m�F����?��(foreachinarea)
 *------------------------------------------
 */
class CSkillCheckConditionChar : public CMapProcessor
{
	map_session_data& tsd;
	unsigned short skillid;
public:
	mutable int& c;
	CSkillCheckConditionChar(map_session_data& s, unsigned short sid, int& cc)
		: tsd(s), skillid(sid), c(cc)	{}
	~CSkillCheckConditionChar()	{}
	virtual int process(block_list& bl) const
	{
		map_session_data &sd = (map_session_data&)bl;
		unsigned int tick = gettick();
		struct pc_base_job s_class = pc_calc_base_job(sd.status.class_);

		//�`�F�b�N���Ȃ��ݒ�Ȃ�c�ɂ��肦�Ȃ��傫��?����Ԃ��ďI��
		if(!config.player_skill_partner_check)
		{	//�{?��foreach�̑O�ɂ�肽�����ǐݒ�K�p�ӏ����܂Ƃ߂邽�߂ɂ�����
			c = 99;
			return 0;
		}

		if(bl.id == tsd.block_list::id)
			return 0;
		switch(skillid)
		{
		case PR_BENEDICTIO:				// ��?�~�� /
		{
			if ((s_class.job == 4 || s_class.job == 8 || s_class.job == 15) &&
					(sd.block_list::x == tsd.block_list::x - 1 || sd.block_list::x == tsd.block_list::x + 1) &&
					sd.status.sp >= 10)
				c++;
			break;
		}
		case BD_LULLABY:				// �q��� 
		case BD_RICHMANKIM:				// �j�����h�̉� 
		case BD_ETERNALCHAOS:			// �i���̍��� 
		case BD_DRUMBATTLEFIELD:		// ?���ۂ̋��� 
		case BD_RINGNIBELUNGEN:			// �j?�x�����O�̎w�� 
		case BD_ROKISWEIL:				// ���L�̋��� 
		case BD_INTOABYSS:				// �[���̒��� 
		case BD_SIEGFRIED:				// �s���g�̃W?�N�t��?�h 
		case BD_RAGNAROK:				// �_?��?�� 
		case CG_MOONLIT:				// ������̐�ɗ�����Ԃт� 
		{
			struct pc_base_job t_class = pc_calc_base_job(tsd.status.class_);
			int skilllv;
			if (((t_class.job == 19 && s_class.job == 20) ||
					(t_class.job == 20 && s_class.job == 19)) &&
			(skilllv = sd.skill_check( skillid)) > 0 &&
					sd.status.party_id && tsd.status.party_id &&
					sd.status.party_id == tsd.status.party_id &&
					!sd.is_sitting() && !sd.is_dead() &&
					c == 0 &&
					sd.skilltimer==-1 &&
					sd.canmove_tick < tick && // added various missing ensemble checks [Valaris]
					!sd.has_status(SC_DANCING) )
			{
				c = skilllv;
			}
			break;
		}
		}//end switch
		return 0;
	}
};
/*==========================================
 * ��??�L�������݊m�F�����X�L���g�p?��(foreachinarea)
 *------------------------------------------
 */

class CSkillCheckConditionUse : public CMapProcessor
{
	map_session_data& ssd;
public:
	mutable int& c;
	CSkillCheckConditionUse(map_session_data& s, int& cc) : ssd(s), c(cc)	{}
	~CSkillCheckConditionUse()	{}
	virtual int process(block_list& bl) const
	{
		map_session_data &sd = (map_session_data &)bl;
		struct pc_base_job s_class;
		struct pc_base_job ss_class;
		int skillid,skilllv;
		unsigned int tick = gettick();

		s_class = pc_calc_base_job(sd.status.class_);

		//�`�F�b�N���Ȃ��ݒ�Ȃ�c�ɂ��肦�Ȃ��傫��?����Ԃ��ďI��
		if(!config.player_skill_partner_check){	//�{?��foreach�̑O�ɂ�肽�����ǐݒ�K�p�ӏ����܂Ƃ߂邽�߂ɂ�����
			c=99;
			return 0;
		}
		ss_class = pc_calc_base_job(ssd.status.class_);
		skillid=ssd.skillid;
		skilllv=ssd.skilllv;
		if(skillid > 0 && skilllv <= 0) return 0;	// celest
		switch(skillid)
		{
		case PR_BENEDICTIO:				// ��?�~�� 
			if (sd.block_list::id != ssd.block_list::id && (s_class.job == 4 || s_class.job == 8 || s_class.job == 15) &&
				(sd.block_list::x == ssd.block_list::x - 1 || sd.block_list::x == ssd.block_list::x + 1) && sd.status.sp >= 10){
				sd.status.sp -= 10;
				clif_updatestatus(sd,SP_SP);
				++c;
			}
			break;
		case BD_LULLABY:				// �q��� 
		case BD_RICHMANKIM:				// �j�����h�̉� 
		case BD_ETERNALCHAOS:			// �i���̍��� 
		case BD_DRUMBATTLEFIELD:		// ?���ۂ̋��� 
		case BD_RINGNIBELUNGEN:			// �j?�x�����O�̎w�� 
		case BD_ROKISWEIL:				// ���L�̋��� 
		case BD_INTOABYSS:				// �[���̒��� 
		case BD_SIEGFRIED:				// �s���g�̃W?�N�t��?�h 
		case BD_RAGNAROK:				// �_?��?�� 
		case CG_MOONLIT:				// ������̐�ɗ�����Ԃт� 
			if(sd.block_list::id != ssd.block_list::id && //�{�l�ȊO��
			  ((ss_class.job==19 && s_class.job==20) || //�������o?�h�Ȃ�_���T?��
			   (ss_class.job==20 && s_class.job==19)) && //�������_���T?�Ȃ�o?�h��
				sd.skill_check(skillid) > 0 && //�X�L���������Ă���
			   c==0 && //�ŏ��̈�l��
			   (sd.weapontype1==13 || sd.weapontype1==14) &&
			   (ssd.weapontype1==13 || ssd.weapontype1==14) &&
			   sd.status.party_id && ssd.status.party_id &&
			   sd.status.party_id == ssd.status.party_id && //�p?�e�B?��������
				!sd.is_sitting() && !sd.is_dead() && //�����ĂȂ�
				!sd.has_status(SC_DANCING) && //�_���X������Ȃ�
			   sd.skilltimer==-1 &&
			   DIFF_TICK(sd.canmove_tick,tick)<0  // added various missing ensemble checks [Valaris]
				)
			{
				ssd.get_statusvalue4(SC_DANCING).integer() = bl.id;
				status_change_start(&bl,SC_DANCING,skillid,ssd.get_statusvalue2(SC_DANCING),0,ssd.block_list::id,skill_get_time(skillid,skilllv)+1000,0);
				clif_skill_nodamage(bl,ssd,skillid,skilllv,1);
				sd.skillid_dance=sd.skillid=skillid;
				sd.skilllv_dance=sd.skilllv=skilllv;
				++c;
			}
			break;
		}
		return 0;
	}
};
/*==========================================
 * ��??�o�C�I�v�����g�A�X�t�B�A�}�C���pMob���݊m�F����?��(foreachinarea)
 *------------------------------------------
 */
class CSkillCheckConditionMobmaster : public CMapProcessor
{
	uint32 src_id;
	int mob_class;
public:
	CSkillCheckConditionMobmaster(uint32 i, int c) : src_id(i), mob_class(c)	{}
	~CSkillCheckConditionMobmaster()	{}
	virtual int process(block_list& bl) const
	{
		struct mob_data *md = bl.get_md();
		if( md && md->class_==mob_class && md->master_id==src_id)
			return 1;
		return 0;
	}
};

class CSkillCheckConditionHermod : public CMapProcessor
{
public:
	CSkillCheckConditionHermod()	{}
	~CSkillCheckConditionHermod()	{}
	virtual int process(block_list& bl) const
	{
		return (NULL!=bl.get_warp());
	}
};


/*==========================================
 * �M�����O�X�^?�p���_�C�X����?��(foreachinarea)
 *------------------------------------------
 */

class CSkillGangsterCount : public CMapProcessor
{
public:
	CSkillGangsterCount()	{}
	~CSkillGangsterCount()	{}
	virtual int process(block_list& bl) const
	{
		map_session_data &sd = (map_session_data&)bl;
		if( sd.is_sitting() && sd.skill_check(RG_GANGSTER) > 0)
			return 1;
		return 0;
	}
};

class CSkillGangsterIn : public CMapProcessor
{
public:
	CSkillGangsterIn()	{}
	~CSkillGangsterIn()	{}
	virtual int process(block_list& bl) const
	{
		map_session_data &sd=(map_session_data&)bl;
		if( sd.is_sitting() && sd.skill_check(RG_GANGSTER) > 0 )
			sd.state.gangsterparadise=1;
		return 0;
	}
};

class CSkillGangsterOut : public CMapProcessor
{
public:
	CSkillGangsterOut()	{}
	~CSkillGangsterOut()	{}
	virtual int process(block_list& bl) const
	{
		map_session_data &sd=(map_session_data&)bl;
		if(sd.state.gangsterparadise)
			sd.state.gangsterparadise=0;
		return 0;
	}
};



/*==========================================
 * �X�L�����j�b�g�^�C�}??��?���p(foreachinarea)
 *------------------------------------------
 */
class CSkillUnitTimerOnplace : public CMapProcessor
{
	struct skill_unit& unit;
	unsigned long tick;
public:
	CSkillUnitTimerOnplace(struct skill_unit& u, unsigned long t)
		: unit(u), tick(t)
	{}
	~CSkillUnitTimerOnplace()	{}
	virtual int process(block_list& bl) const
	{
		struct skill_unit_group *group = unit.group;
		if( bl!=BL_PC && bl!=BL_MOB ||
			!unit.alive || !bl.is_on_map() )
			return 0;
		nullpo_retr(0, group);
		if (battle_check_target(&unit,&bl,group->target_flag)<=0)
			return 0;
		skill_unit_onplace_timer(&unit,&bl,tick);
		return 0;
	}
};
/*==========================================
 * �X�L�����j�b�g�^�C�}??���p(foreachobject)
 *------------------------------------------
 */

class CSkillUnitTimer : public CMapProcessor
{
	ICL_EMPTY_COPYCONSTRUCTOR(CSkillUnitTimer)
	unsigned long tick;
public:
	CSkillUnitTimer(unsigned long t)
		: tick(t)
	{}
	~CSkillUnitTimer()	{}
	virtual int process(block_list& bl) const
	{
		struct skill_unit& unit = (struct skill_unit&)bl;
		struct skill_unit_group *group = unit.group;
		int range = unit.range;

		if(!unit.alive)
			return 0;

		nullpo_retr(0, group);

		// onplace_timer�C�x���g�Ăяo�� 
		if (range>=0 && group->interval!=-1)
		{
			maps[bl.m].foreachinarea( CSkillUnitTimerOnplace(unit,tick),
				bl.x, bl.y, range, BL_ALL);

			if (!unit.alive)
				return 0;

			// �}�O�k�X�͔����������j�b�g�͍폜����
			if(group->skill_id==PR_MAGNUS && unit.val2)
			{
				skill_delunit(&unit);
				return 0;
			}
		}
		// �C�h�D���̗ь�ɂ���
		if (group->unit_id==0xaa && DIFF_TICK(tick,group->tick)>=6000*group->val3)
		{
			block_list *src = block_list::from_blid(group->src_id);
			nullpo_retr(0, src);
			range = skill_get_unit_layout_type(group->skill_id,group->skill_lv);
			maps[src->m].foreachinarea( CSkillIdunheal(unit),
				src->x, src->y, range, BL_ALL);
			group->val3++;
		}
		// ���Ԑ؂�폜 
		if((DIFF_TICK(tick,group->tick)>=group->limit || DIFF_TICK(tick,group->tick)>=unit.limit)){
			switch(group->unit_id){
				case UNT_BLASTMINE:	// �u���X�g�}�C�� 
					group->unit_id = UNT_USEDTRAP;
					clif_changelook(bl,LOOK_BASE,group->unit_id);
					group->limit=DIFF_TICK(tick+1500,group->tick);
					unit.limit=DIFF_TICK(tick+1500,group->tick);
					break;
				case UNT_SKIDTRAP:	// �X�L�b�h�g���b�v 
				case UNT_ANKLESNARE:	// �A���N���X�l�A 
				case UNT_LANDMINE:	// �����h�}�C�� 
				case UNT_SHOCKWAVE:	// �V���b�N�E�F?�u�g���b�v 
				case UNT_SANDMAN:	// �T���h�}�� 
				case UNT_FLASHER:	// �t���b�V��? 
				case UNT_FREEZINGTRAP:	// �t��?�W���O�g���b�v 
				case UNT_CLAYMORETRAP:	// �N���C���A?�g���b�v 
				case UNT_TALKIEBOX:	// �g?�L?�{�b�N�X 
					{
						block_list *src=block_list::from_blid(group->src_id);
						if(group->unit_id == UNT_ANKLESNARE && group->val2)
							;
						else
						{
							if(src && *src==BL_PC)
							{
								struct item item_tmp(1065);
								flooritem_data::create(item_tmp,1,bl.m,bl.x,bl.y,NULL,NULL,NULL,0);	// ?�Ԋ�
							}
						}
						skill_delunit(&unit);
					}
					break;

				case 0xc1:
				case 0xc2:
				case 0xc3:
				case 0xc4:
					{
						block_list *src=block_list::from_blid(group->src_id);
						if (src)
							group->tick = tick;
					}
					break;

				default:
					skill_delunit(&unit);
			}
		}
		// setting ice wall to change back?
		if(group->unit_id == 0x8d) {
			unit.val1 -= 5;
			if(unit.val1 <= 0 && unit.limit + group->tick > tick + 700)
				unit.limit = DIFF_TICK(tick+700,group->tick);
		}
		return 0;
	}
};

/*==========================================
 * �X�L�����j�b�g�ړ���?���p(foreachinarea)
 *------------------------------------------
 */
class CSkillUnitMove : public CMapProcessor
{
	block_list& target;
	unsigned long tick;
	int flag;
public:
	CSkillUnitMove(block_list& tar, unsigned long t, int f)
		: target(tar), tick(t), flag(f)
	{}
	~CSkillUnitMove()	{}
	virtual int process(block_list& bl) const
	{
		struct skill_unit &unit = (struct skill_unit &)bl;
		struct skill_unit_group *group=unit.group;
		nullpo_retr(0, group);
		if (group->interval!=-1)
			return 0;
		if (!unit.alive)
			return 0;
		if (flag)
			skill_unit_onplace(&unit,&target,tick);
		else
			skill_unit_onout(&unit,&target,tick);
		return 0;
	}
};


// Making plagirize check its own function [Aru]
bool skill_can_copy(map_session_data &sd, unsigned short skillid)
{
	// NPC Skills, never ok to copy
	if(skillid >= NPC_PIERCINGATT && skillid <= NPC_SUMMONMONSTER)
		return false;
	if(skillid >= NPC_RANDOMMOVE && skillid <= NPC_RUN)
		return false;
	if(skillid >= WE_BABY && skillid <= NPC_EMOTION_ON)
		return false;

	// High-class skills
	if(skillid >= LK_AURABLADE)
	{
		if(config.copyskill_restrict == 2)
			return false;
		else if(config.copyskill_restrict)
			return (sd.status.class_ == 4018);
	}
	return true;
}


// [MouseJstr] - skill ok to cast? and when?
int skill_not_ok(int skillid, map_session_data &sd)
{	
	if (!(skillid >= 10000 && skillid < 10015))
		if ((skillid > MAX_SKILL) || (skillid < 0))
			return 1;

	{
		int i = skillid;
		if (i >= 10000 && i < 10015)
			i -= 9500;
		if (sd.blockskill[i] > 0)
			return 1;
	}

	if (sd.isGM() >= 20)
		return 0;  // gm's can do anything damn thing they want

	// Check skill restrictions [Celest]
	if(!maps[sd.block_list::m].flag.pvp && !maps[sd.block_list::m].flag.gvg && skill_get_nocast (skillid) & 1)
		return 1;
	if(maps[sd.block_list::m].flag.pvp && skill_get_nocast (skillid) & 2)
		return 1;
	if(maps[sd.block_list::m].flag.gvg && skill_get_nocast (skillid) & 4)
		return 1;
	if (agit_flag && skill_get_nocast (skillid) & 8)
		return 1;
	if (config.pk_mode && !maps[sd.block_list::m].flag.nopvp && skill_get_nocast (skillid) & 16)
		return 1;

	if(skillid == LK_BERSERK && DIFF_TICK(gettick(),sd.canregen_tick)<0)
		return 1;
	
	switch (skillid) {
		case AL_WARP:
		case AL_TELEPORT:
		case MC_VENDING:
		case MC_IDENTIFY:
			return 0; // always allowed
		default:
			return (maps[sd.block_list::m].flag.noskill);
	}
}


// �X�L�����j�b�g�̔z�u����Ԃ� 
struct skill_unit_layout skill_unit_layout[MAX_SKILL_UNIT_LAYOUT];
int firewall_unit_pos;
int icewall_unit_pos;

struct skill_unit_layout *skill_get_unit_layout(int skillid, int skilllv, block_list *src, int x, int y)
{	
	int pos = skill_get_unit_layout_type(skillid,skilllv);
	dir_t dir;
	if(pos != -1)
		return &skill_unit_layout[pos];

	if (src->x == x && src->y == y)
		dir = DIR_E;
	else
		dir = src->get_direction(x,y);

	if (skillid == MG_FIREWALL)
		return &skill_unit_layout[firewall_unit_pos + dir];
	else if (skillid == WZ_ICEWALL)
		return &skill_unit_layout[icewall_unit_pos + dir];

	ShowMessage("unknown unit layout for skill %d, %d\n",skillid,skilllv);
	return &skill_unit_layout[0];
}

//	0x89,0x8a,0x8b �\������
//	0x9a ��?���̉r���݂����ȃG�t�F�N�g
//	0x9b ��?���̉r���݂����ȃG�t�F�N�g
//	0x9c ��?���̉r���݂����ȃG�t�F�N�g
//	0x9d ���������ȃG�t�F�N�g
//	0xb1 Alchemist Demonstration
//	0xb2 = Pink Warp Portal
//	0xb3 = Gospel For Paladin
//	0xb4 = Basilica
//	0xb5 = Empty
//	0xb6 = Fog Wall for Professor
//	0xb7 = Spider Web for Professor
//	0xb8 = Empty
//	0xb9 = UNT_HERMODE

/*==========================================
 * �X�L���ǉ�?��
 *------------------------------------------
 */
int skill_additional_effect(block_list* src, block_list *bl,unsigned short skillid,unsigned short skilllv,int attack_type,unsigned long tick)
{
	// MOB�ǉ�?�ʃX�L���p 
// dangerous reverse access
//	this structure here depends on an extern enum
//	const int sc[]={
//		SC_POISON, SC_BLIND, SC_SILENCE, SC_STUN,
//		SC_STONE, SC_CURSE, SC_SLEEP
//	};
	// this is ok, access is by index
	const int sc2[]={ //Note: We use Sonic Blow's stun duration for the confusion lasting time (dummy value): 12 secs at lv7
		MG_STONECURSE,MG_FROSTDIVER,NPC_STUNATTACK,
		NPC_SLEEPATTACK,TF_POISON,NPC_CURSEATTACK,
		NPC_SILENCEATTACK,AS_SONICBLOW,NPC_BLINDATTACK,
		LK_HEADCRUSH
	};

	map_session_data *sd=NULL;
	map_session_data *dstsd=NULL;
	struct mob_data *md=NULL;
	struct mob_data *dstmd=NULL;

	int skill,skill2;
	int rate;

	int sc_def_mdef,sc_def_vit,sc_def_int,sc_def_luk;
	int sc_def_mdef2,sc_def_vit2,sc_def_int2,sc_def_luk2;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	if(skillid > 0 && skilllv <= 0) return 0;	// don't forget auto attacks! - celest


	if( !(sd = src->get_sd()) && !(md = src->get_md()) && !src->get_pd() )
	{	//PC,MOB�ȊO�͒ǉ����ʂ̑ΏۊO
		return 0;
	}
	(dstmd=bl->get_md()) || (dstsd=bl->get_sd());


	//?�ۂ̑ϐ�
	sc_def_mdef = status_get_sc_def_mdef(bl);
	sc_def_vit = status_get_sc_def_vit(bl);
	sc_def_int = status_get_sc_def_int(bl);
	sc_def_luk = status_get_sc_def_luk(bl);

	//�����̑ϐ�
	sc_def_mdef2 = status_get_sc_def_mdef(src);
	sc_def_vit2 = status_get_sc_def_vit(src);
	sc_def_int2 = status_get_sc_def_int(src);
	sc_def_luk2 = status_get_sc_def_luk(src);

	switch(skillid){
	case 0:					// �ʏ�U? 
		// ������ 
		if(sd)
		{
			if( sd->is_falcon() && sd->status.weapon == 11 && (skill=sd->skill_check(HT_BLITZBEAT))>0 &&
				rand()%1000 <= sd->paramc[5]*10/3+1 ) {
				int lv=(sd->status.job_level+9)/10;
				skill_castend_damage_id(src,bl,HT_BLITZBEAT,(skill<lv)?skill:lv,tick,0xf00000);
			}
			// �X�i�b�`��?
			if(dstmd && !dstmd->state.steal_flag && sd->status.weapon != 11 && (skill=sd->skill_check(RG_SNATCHER)) > 0 &&
				(skill*15 + 55) + (skill2 = sd->skill_check(TF_STEAL))*10 > rand()%1000) {
				if(pc_steal_item(*sd,bl))
					clif_skill_nodamage(*src,*bl,TF_STEAL,skill2,1);
				else if (config.display_snatcher_skill_fail)
					sd->skill_failed(skillid);
			}
			// enchant poison has a chance of poisoning enemy
			if( sd->has_status(SC_ENCPOISON) && !bl->has_status(SC_POISON) &&
				rand() % 100 < sd->get_statusvalue1(SC_ENCPOISON).integer() * sc_def_vit / 100)
			{
				status_change_start(bl,SC_POISON,sd->get_statusvalue1(SC_ENCPOISON).integer(),
					0,0,0,skill_get_time2(AS_ENCHANTPOISON,sd->get_statusvalue1(SC_ENCPOISON).integer()),0);
			}
			// �G���`�����g�f�b�g��?�|�C�Y��(�ғ�?��)
			if (sd->has_status(SC_EDP) && !(bl->get_mode() & 0x20) &&
				!bl->has_status(SC_DPOISON) &&
				rand() % 100 < sd->get_statusvalue2(SC_EDP).integer() * sc_def_vit / 100)
				status_change_start(bl,SC_DPOISON,sd->get_statusvalue1(SC_EDP).integer(),
					0,0,0,skill_get_time2(ASC_EDP,sd->get_statusvalue1(SC_EDP).integer()),0);			
		}
		break;

	case SM_BASH:			// �o�b�V���i�}���U?�j
		if( sd && skilllv > 5 && (skill=sd->skill_check(SM_FATALBLOW))>0 ){
			if( rand()%100 < (6*(skilllv-5)+sd->status.base_level/10)*sc_def_vit/100 ) //TODO: How much % per base level it actually is?
				status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(SM_FATALBLOW,skilllv),0);
		}
		break;

	case TF_POISON:			// �C���x�i��
	case AS_SPLASHER:		// �x�i���X�v���b�V��?
		if(rand()%100< (2*skilllv+10)*sc_def_vit/100 )
			status_change_start(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		else{
			if(sd && skillid==TF_POISON)
				sd->skill_failed(skillid);
		}
		break;

	case AS_SONICBLOW:		// �\�j�b�N�u��?
		if( rand()%100 < (2*skilllv+10)*sc_def_vit/100 )
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case AS_GRIMTOOTH:
	{
			if( !bl->has_status(SC_SLOWDOWN) )
				status_change_start(bl,SC_SLOWDOWN,0,0,0,0,1000,0);
		break;
	}
	case HT_FREEZINGTRAP:	// �t��?�W���O�g���b�v 
		if(dstmd || (dstsd && (maps[bl->m].flag.pvp || maps[bl->m].flag.gvg)) ) {
			rate = skilllv*3 + 35;
			if(rand()%100 < rate*sc_def_mdef/100)
				status_change_start(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		}
		break;

	 case HT_FLASHER:  // Flasher 
		if (!(bl->get_mode() & 0x20) && !(bl->get_mode()&0x40) &&
				((dstsd && md) || (dstmd && !md) || (dstsd && (maps[bl->m].flag.pvp || maps[bl->m].flag.gvg))) &&
				rand()%100 < (10*skilllv+30)*sc_def_int/100)
			status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case MG_FROSTDIVER:		// �t���X�g�_�C�o? 
	case WZ_FROSTNOVA:		// �t���X�g�m���@ 
		{
			rate = (skilllv*3+35)*sc_def_mdef/100-(bl->get_int()+bl->get_luk())/15;
			if (rate <= 5)
				rate = 5;
			if( !bl->has_status(SC_FREEZE) && rand()%100 < rate)
				status_change_start(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv)*(1-sc_def_mdef/100),0);
		}
		break;

	case WZ_STORMGUST:		// �X�g?���K�X�g
		{
			++bl->get_statusvalue3(SC_FREEZE).integer();
			if(bl->get_statusvalue3(SC_FREEZE).integer() >= 3)
				status_change_start(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		}
		break;

	case HT_LANDMINE:		// �����h�}�C��
		if( *bl==BL_MOB || (*bl== BL_PC && (maps[bl->m].flag.pvp || maps[bl->m].flag.gvg)) )
			if( rand()%100 < (5*skilllv+30)*sc_def_vit/100 )
				status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case HT_SHOCKWAVE:				//it can't affect mobs, because they have no SP...
		if( dstsd && (maps[bl->m].flag.pvp || maps[bl->m].flag.gvg) ){
			dstsd->status.sp -= dstsd->status.sp*(5+15*skilllv)/100;
			status_calc_pc(*dstsd,0);
		}
		break;
	case HT_SANDMAN:		// �T���h�}��
		if( *bl== BL_MOB || (*bl== BL_PC && (maps[bl->m].flag.pvp || maps[bl->m].flag.gvg)) )
			if( rand()%100 < (5*skilllv+30)*sc_def_int/100 )
				status_change_start(bl,SC_SLEEP,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case TF_SPRINKLESAND:	// ���܂�
		if( rand()%100 < 20*sc_def_int/100 )
			status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case TF_THROWSTONE:		// �Γ���
		if( rand()%100 < 3*sc_def_vit/100 )
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		if( rand()%100 < 3*sc_def_int/100 )
			status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);

		break;

	case NPC_DARKCROSS:
	case CR_HOLYCROSS:		// �z?��?�N���X
		if( rand()%100 < 3*skilllv*sc_def_int/100 )
			status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case CR_GRANDCROSS:		// �O�����h�N���X
	case NPC_GRANDDARKNESS:	// �ŃO�����h�N���X
		{
			int race = bl->get_race();
			if( (bl->is_undead() || race == 6) && rand()%100 < 100000*sc_def_int/100)	//?���t?�������S�ϐ��ɂ͖�?
				status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		}
		break;

	case AM_ACIDTERROR:
		if (rand()%100 < (skilllv*3)*sc_def_vit/100 ) {
			int bleed_time = skill_get_time2(skillid,skilllv) - bl->get_vit() * 1000;
			if (bleed_time < 50000)
				bleed_time = 50000;	// minimum 50 seconds
			status_change_start(bl,SC_BLEEDING,skilllv,0,0,0,bleed_time,0);
		}
		break;
	case AM_DEMONSTRATION:
		if (dstsd && (size_t)rand()%10000 < skilllv * config.equip_skill_break_rate )
			pc_breakweapon(*dstsd);
		break;
		
	case CR_SHIELDCHARGE:		// �V?���h�`��?�W
		if( rand()%100 < (15 + skilllv*5)*sc_def_vit/100 )
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case PA_PRESSURE:	// �v���b�V��?
		{	// Official servers seem to indicate this causes neither stun nor bleeding. [Skotlex]
			int race = bl->get_race();
			int bleed_time = skill_get_time2(skillid,skilllv) - bl->get_vit() * 1000;
			if (bleed_time < 60000)
				bleed_time = 60000;	// minimum time for pressure is?
			if (rand()%100 < 50 * sc_def_vit / 100)	// is chance 50%?
				status_change_start(bl, SC_STUN, skilllv, 0, 0, 0, skill_get_time2(PA_PRESSURE,skilllv), 0);
			if (!(bl->is_undead() || race == 6) && rand()%100 < 50 * sc_def_vit / 100)
				status_change_start(bl, SC_BLEEDING, skilllv, 0, 0, 0, bleed_time, 0);
			if (dstsd) {
				dstsd->status.sp -= dstsd->status.sp * (15 + 5 * skilllv) / 100;
				clif_updatestatus(*dstsd,SP_SP);
			}
		}
		break;

	case RG_RAID:		// �T�v���C�Y�A�^�b�N
		if( rand()%100 < (10+3*skilllv)*sc_def_vit/100 )
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		if( rand()%100 < (10+3*skilllv)*sc_def_int/100 )
			status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case BA_FROSTJOKE:
		if(rand()%100 < (15+5*skilllv)*sc_def_mdef/100)
			status_change_start(bl,SC_FREEZE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case DC_SCREAM:
		if( rand()%100 < (25+5*skilllv)*sc_def_vit/100 )
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case BD_LULLABY:	// �q��S
		if( rand()%100 < 15*sc_def_int/100 )
			status_change_start(bl,SC_SLEEP,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	// MOB�̒ǉ�?�ʕt���X�L��

	case NPC_PETRIFYATTACK:
		if(rand()%100 < sc_def_mdef)
			//status_change_start(bl,sc[skillid-NPC_POISON],skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			status_change_start(bl,SC_STONE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_POISON:
		if(*src==BL_PET)
			status_change_start(bl,SC_POISON,skilllv,0,0,0,skilllv*1000,0);
		else if(rand()%100 < sc_def_vit)
			status_change_start(bl,SC_POISON,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_SILENCEATTACK:
		if(*src==BL_PET)
			status_change_start(bl,SC_SILENCE,skilllv,0,0,0,skilllv*1000,0);
		else if(rand()%100 < sc_def_vit)
			status_change_start(bl,SC_SILENCE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_STUNATTACK:
		if(*src==BL_PET)
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skilllv*1000,0);
		else if(rand()%100 < sc_def_vit)
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_CURSEATTACK:
		if(rand()%100 < sc_def_luk)
			status_change_start(bl,SC_CURSE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_SLEEPATTACK:
		if(rand()%100 < sc_def_int)
			status_change_start(bl,SC_SLEEP,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_BLINDATTACK:
		if(rand()%100 < sc_def_int)
			status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case NPC_MENTALBREAKER:
		if(dstsd) {
			int sp = dstsd->status.max_sp*(10+skilllv)/100;
			if(sp < 1) sp = 1;
			dstsd->heal(0,-sp);
		}
		break;

// -- moonsoul (adding status effect chance given to wizard aoe skills meteor and vermillion)
//
	case WZ_METEOR:
		if(rand()%100 < sc_def_vit)
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case WZ_VERMILION:
		if(rand()%100 < sc_def_int)
			status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

// -- moonsoul (stun ability of new champion skill tigerfist)
//
	case CH_TIGERFIST:
		if (rand()%100 < (10 + skilllv*10)*sc_def_vit/100) {
			int sec = skill_get_time2 (skillid,skilllv) - bl->get_agi()/10;
			if (dstsd) {
				dstsd->canmove_tick += sec;
				dstsd->canact_tick += sec;
			} else if (dstmd)
				dstmd->canmove_tick += sec;
		}
		break;

	case LK_SPIRALPIERCE:
		if (rand()%100 < (15 + skilllv*5)*sc_def_vit/100) {
			int sec = skill_get_time2 (skillid,skilllv);
			if (dstsd) {
				dstsd->canmove_tick += sec;
			} else if (dstmd)
				dstmd->canmove_tick += sec;
		}
		// changed to 'unable to move' instead of stun [celest]
		//status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case ST_REJECTSWORD:	// �t��?�W���O�g���b�v
		if( rand()%100 < (skilllv*15) )
			status_change_start(bl,SC_AUTOCOUNTER,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case PF_FOGWALL:		// �z?��?�N���X
		if (src != bl)
		{
			if( !bl->has_status(SC_DELUGE) )
				status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		}
		break;
	case LK_HEADCRUSH:				// �w�b�h�N���b�V��
		{
			//?�����ǂ�������Ȃ��̂œK?��
			int race = bl->get_race();
			int bleed_time = skill_get_time2(skillid,skilllv) - bl->get_vit() * 1000;
			if (bleed_time < 90000)
				bleed_time = 90000;	// minimum 90 seconds
			if (!(bl->is_undead() || race == 6) && rand()%100 < 50 * sc_def_vit/100)
				status_change_start(bl, (status_t)SkillStatusChangeTable[skillid], skilllv, 0, 0, 0, bleed_time, 0);
		}
			break;
	case LK_JOINTBEAT:				// �W���C���g�r?�g
		//?�����ǂ�������Ȃ��̂œK?��
		if( rand()%100 < (5*skilllv+5)*sc_def_vit/100 )
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;
	case PF_SPIDERWEB:		// �X�p�C�_?�E�F�b�u
		{
			int sec = skill_get_time2(skillid,skilllv);
			if(maps[src->m].flag.pvp) //PvP�ł͍S�����Ԕ����H
				sec = sec/2;
			bl->stop_walking(1);
			status_change_start(bl,SC_SPIDERWEB,skilllv,0,0,0,sec,0);
		}
		break;
	case ASC_METEORASSAULT:			// ���e�I�A�T���g
/*		if( rand()%100 < (15 + skilllv*5)*sc_def_vit/100 ) //?�Ԉُ�͏ڍׂ�������Ȃ��̂œK?��
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		if( rand()%100 < (10+3*skilllv)*sc_def_int/100 )
			status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
*/
		//Any enemies hit by this skill will receive Stun, Darkness, or external bleeding status ailment with a 5%+5*SkillLV% chance.
		if( rand()%100 < (5+skilllv*5) ) //5%+5*SkillLV%
			switch(rand()%3) {
				case 0:
					status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
					break;
				case 1:
					{
					int bleed_time = skill_get_time2(skillid,skilllv) - bl->get_vit() * 1000;
					if (bleed_time < 30000)
					bleed_time = 30000;	// minimum 30 seconds (it could be up to 60 sec.. but no info yet)
					status_change_start(bl,SC_BLEEDING,skilllv,0,0,0,bleed_time,0);
					}
					break;
				default:
					status_change_start(bl,SC_BLIND,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
  			}
		break;
	case MO_EXTREMITYFIST:			// ���C���e����
		//���C�����g����5���Ԏ��R�񕜂��Ȃ��悤�ɂȂ�
		status_change_start(src,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time2(skillid,skilllv),0 );
		break;
	case HW_NAPALMVULCAN:			// �i�p?���o���J��
		// skilllv*5%�̊m���Ŏ�
		if (rand()%10000 < 5*skilllv*sc_def_luk)
			status_change_start(bl,SC_CURSE,7,0,0,0,skill_get_time2(NPC_CURSEATTACK,7),0);
		break;

	case WS_CARTTERMINATION:	// Cart termination
		if (rand() % 10000 < 5 * skilllv * sc_def_vit)
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(WS_CARTTERMINATION,skilllv),0);
		break;

	case CR_ACIDDEMONSTRATION:
		if (dstsd) {
			if ((rand() % 100) * config.equip_skill_break_rate/100  < skilllv)
				pc_breakweapon(*dstsd);
			// separate chances?
			if ((rand() % 100) * config.equip_skill_break_rate/100 < skilllv)
				pc_breakarmor(*dstsd);
		}
		break;

	// Taekwon skills
	case TK_DOWNKICK:
		if(rand()%100< 100*sc_def_vit/100 ) {
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	}// end switch

	if((sd||dstsd) && skillid != MC_CARTREVOLUTION && attack_type&BF_WEAPON){	// �J?�h�ɂ��ǉ�?��
		int i, type;
		int sc_def_card=100;

		for(i=SC_STONE;i<=SC_BLEEDING;++i){
			type=i-SC_STONE;
			//?�ۂ�?�Ԉُ�
			switch (i) {
				case SC_STONE:
				case SC_FREEZE:
					sc_def_card=sc_def_mdef;
					break;
				case SC_STUN:
				case SC_POISON:
				case SC_SILENCE:
				case SC_BLEEDING:
					sc_def_card=sc_def_vit;
					break;
				case SC_SLEEP:
				case SC_CONFUSION:
				case SC_BLIND:
					sc_def_card=sc_def_int;
					break;
				case SC_CURSE:
					sc_def_card=sc_def_luk;
			}

			if (sd) {
				if(!sd->state.arrow_atk) {
					if(rand()%10000 < (sd->addeff[type])*sc_def_card/100 ){
						if(config.battle_log)
							ShowMessage("PC %d skill_addeff: card�ɂ��ُ�?�� %d %d\n",sd->block_list::id,i,sd->addeff[type]);
						status_change_start(bl,(status_t)i,7,0,0,0,(i==SC_CONFUSION)? 10000+7000:skill_get_time2(sc2[type],7),0);
					}
				} else {
					if(rand()%10000 < (sd->addeff[type]+sd->arrow_addeff[type])*sc_def_card/100 ){
						if(config.battle_log)
							ShowMessage("PC %d skill_addeff: card�ɂ��ُ�?�� %d %d\n",sd->block_list::id,i,sd->addeff[type]);
						status_change_start(bl,(status_t)i,7,0,0,0,(i==SC_CONFUSION)? 10000+7000:skill_get_time2(sc2[type],7),0);
					}
				}
			}
			//������?�Ԉُ�
			switch (i) {
				case SC_STONE:
				case SC_FREEZE:
					sc_def_card=sc_def_mdef2;
					break;
				case SC_STUN:
				case SC_POISON:
				case SC_SILENCE:
					sc_def_card=sc_def_vit2;
					break;
				case SC_SLEEP:
				case SC_CONFUSION:
				case SC_BLIND:
					sc_def_card=sc_def_int2;
					break;
				case SC_CURSE:
					sc_def_card=sc_def_luk2;
			}

			if (sd) {
				if(!sd->state.arrow_atk) {
					if(rand()%10000 < (sd->addeff2[type])*sc_def_card/100 ){
						if(config.battle_log)
							ShowMessage("PC %d skill_addeff: card�ɂ��ُ�?�� %d %d\n",src->id,i,sd->addeff2[type]);
						status_change_start(src,(status_t)i,7,0,0,0,(i==SC_CONFUSION)? 10000+7000:skill_get_time2(sc2[type],7),0);
					}
				} else {
					if(rand()%10000 < (sd->addeff2[type]+sd->arrow_addeff2[type])*sc_def_card/100 ){
						if(config.battle_log)
							ShowMessage("PC %d skill_addeff: card�ɂ��ُ�?�� %d %d\n",src->id,i,sd->addeff2[type]);
						status_change_start(src,(status_t)i,7,0,0,0,(i==SC_CONFUSION)? 10000+7000:skill_get_time2(sc2[type],7),0);
					}
				}
			}
			if (dstsd && rand()%10000 < dstsd->addeff3[type]*sc_def_card/100){
				if (dstsd->addeff3_type[type] != 1 && ((sd && !sd->state.arrow_atk) || (src->get_range()<=2)))
					continue;
				if(config.battle_log)
					ShowMessage("PC %d skill_addeff: card�ɂ��ُ�?�� %d %d\n",src->id,i,dstsd->addeff3[type]);
				status_change_start(src,(status_t)i,7,0,0,0,(i==SC_CONFUSION)? 10000+7000:skill_get_time2(sc2[type],7),0);
			}
		}
	}
	return 0;
}

/*=========================================================================
 �X�L���U?������΂�?��
-------------------------------------------------------------------------*/
int skill_blown(block_list *src, block_list *target,int count)
{
	int dx=0,dy=0,nx,ny;
	int x=target->x,y=target->y;
	dir_t dir;
//	int prev_state=MS_IDLE;
	int moveblock;
	map_session_data *sd=NULL;
	struct mob_data *md=NULL;
	struct pet_data *pd=NULL;
	struct skill_unit *su=NULL;

	nullpo_retr(0, src);
	nullpo_retr(0, target);

	if( !(sd=target->get_sd()) &&
		!(md=target->get_md()) &&
		!(pd=target->get_pd()) &&
		!(su=target->get_sk()) )
		return 0;

	if(md && md->mode&(0x40)) //Avoid Pushing inmobile Plants [Skotlex]
		return 0;

	if (count&0xf00000)
		dir = (dir_t)((count>>20)&0x7);
	else if (count&0x10000 || (target->x==src->x && target->y==src->y))
		dir = target->get_dir();
	else
		dir = target->get_direction(*src);
	if (dir>=0 && dir<8){
		dx = -dirx[dir];
		dy = -diry[dir];
	}

	path_blownpos(target->m,x,y,dx,dy,count&0xffff, nx, ny);
	moveblock=( x/BLOCK_SIZE != nx/BLOCK_SIZE || y/BLOCK_SIZE != ny/BLOCK_SIZE);

	if(count&0x20000)
	{
		target->stop_walking(1);
		if(sd)
		{
			sd->walktarget.x=nx;
			sd->walktarget.y=ny;
			clif_moveobject(*sd);
		}
		else if(md)
		{
			md->walktarget.x=nx;
			md->walktarget.y=ny;
			clif_fixobject(*md);
		}
		else if(pd)
		{
			pd->walktarget.x=nx;
			pd->walktarget.y=ny;
			clif_fixobject(*pd);
		}
	}
	else
		target->stop_walking(2);

	dx = nx - x;
	dy = ny - y;

	maps[target->block_list::m].foreachinmovearea( CClifOutsight(*target),
		x-AREA_SIZE,y-AREA_SIZE,x+AREA_SIZE,y+AREA_SIZE,dx,dy,target->get_sd()?BL_ALL:BL_PC);

	if( target->has_status(SC_DANCING) )
	{
		struct skill_unit_group *ptr = (struct skill_unit_group *)target->get_statusvalue2(SC_DANCING).pointer();
		if(ptr) skill_unit_move_unit_group(*ptr, target->m, dx, dy);
	}

	if(su)
	{
		if(su->group) skill_unit_move_unit_group(*su->group,target->m,dx,dy);
	}
	else
	{
		unsigned long tick = gettick();
		skill_unit_move(*target,tick,0);
		if(moveblock) target->delblock();
		target->x=nx;
		target->y=ny;
		if(moveblock) target->addblock();
		skill_unit_move(*target,tick,1);
	}

	maps[target->block_list::m].foreachinmovearea( CClifInsight(*target),
		nx-AREA_SIZE,ny-AREA_SIZE,nx+AREA_SIZE,ny+AREA_SIZE,-dx,-dy,target->get_sd()?BL_ALL:BL_PC);

	if(count&0x20000)
		target->stop_walking();

	return 0;
}


/*
 * =========================================================================
 * �X�L���U??��?���܂Ƃ�
 * flag��?���B16�i?
 *	00XRTTff
 *  ff	= magic�Ōv�Z�ɓn�����j
 *	TT	= �p�P�b�g��type����(0�Ńf�t�H���g�j
 *  X   = �p�P�b�g�̃X�L��Lv
 *  R	= �\��iskill_area_sub�Ŏg�p����j
 *-------------------------------------------------------------------------
 */

int skill_attack(int attack_type, block_list* src, block_list *dsrc,
	 block_list *bl,unsigned short skillid,unsigned short skilllv,unsigned long tick,int flag )
{
	struct Damage dmg;
	int type,lv,damage;
	static int tmpdmg = 0;


	if(skillid > 0 && skilllv <= 0) return 0;

	rdamage = 0;
	nullpo_retr(0, src);
	nullpo_retr(0, dsrc);
	nullpo_retr(0, bl);


//�������Ȃ����肱������
	if(dsrc->m != bl->m) //?�ۂ������}�b�v�ɂ��Ȃ���Ή������Ȃ�
		return 0;
	if( !src->is_on_map() || !dsrc->is_on_map() || !bl->is_on_map() ) //prev�悭�킩��Ȃ���
		return 0;
	if(*src == BL_PC && ((map_session_data *)src)->is_dead()) //�p�ҁH��PC�ł��łɎ���ł����牽�����Ȃ�
		return 0;
	if(src != dsrc && *dsrc == BL_PC && ((map_session_data *)dsrc)->is_dead() ) //�p�ҁH��PC�ł��łɎ���ł����牽�����Ȃ�
		return 0;
	if( *bl== BL_PC && ((map_session_data *)bl)->is_dead() ) //?�ۂ�PC�ł��łɎ���ł����牽�����Ȃ�
		return 0;
	if(*src == BL_PC && skill_not_ok(skillid, *((map_session_data *)src)))
	        return 0; // [MouseJstr]
	if(bl->has_status(SC_HIDING))
	{	//�n�C�f�B���O?�Ԃ�
		if(skill_get_pl(skillid) != 2) //�X�L����?�����n?���łȂ���Ή������Ȃ�
			return 0;
	}
	if(bl->has_status(SC_TRICKDEAD)) //���񂾂ӂ蒆�͉������Ȃ�
		return 0;
	if(skillid == WZ_STORMGUST) { //�g�p�X�L�����X�g?���K�X�g��
		if(bl->has_status(SC_FREEZE)) //����?�ԂȂ牽�����Ȃ�
			return 0;
	}
	if(skillid == WZ_FROSTNOVA && dsrc->x == bl->x && dsrc->y == bl->y) //�g�p�X�L�����t���X�g�m���@�ŁAdsrc��bl�������ꏊ�Ȃ牽�����Ȃ�
		return 0;
	if(*src == BL_PC && ((map_session_data *)src)->chat) //�p�҂�PC�Ń`���b�g���Ȃ牽�����Ȃ�
		return 0;
	if(*dsrc== BL_PC && ((map_session_data *)dsrc)->chat) //�p�҂�PC�Ń`���b�g���Ȃ牽�����Ȃ�
		return 0;
	if(*src == BL_PC && bl && mob_gvmobcheck(*((map_session_data *)src),*bl)==0)
		return 0;

//�������Ȃ����肱���܂�

	type=-1;
	lv=(flag>>20)&0xf;
	dmg=battle_calc_attack(attack_type,src,bl,skillid,skilllv,flag&0xff ); //�_��?�W�v�Z

//�}�W�b�N���b�h?����������
	if(attack_type&BF_MAGIC && bl->has_status(SC_MAGICROD) && src == dsrc)
	{	//���@�U?�Ń}�W�b�N���b�h?�Ԃ�src=dsrc�Ȃ�
		dmg.damage = dmg.damage2 = 0; //�_��?�W0
		map_session_data *sd = bl->get_sd();
		if(sd)
		{ //?�ۂ�PC�̏ꍇ
			int sp = skill_get_sp(skillid,skilllv); //�g�p���ꂽ�X�L����SP���z?
			sp = sp * bl->get_statusvalue2(SC_MAGICROD).integer() / 100; //�z?���v�Z
			if(skillid == WZ_WATERBALL && skilllv > 1) //�E�H?�^?�{?��Lv1�ȏ�
				sp = sp/((skilllv|1)*(skilllv|1)); //����Ɍv�Z�H
			if(sp > 0x7fff) sp = 0x7fff; //SP�������̏ꍇ�͗��_�ő�l
			else if(sp < 1) sp = 1; //1�ȉ��̏ꍇ��1
			if(sd->status.sp + sp > sd->status.max_sp) { //��SP+���݂�SP��MSP���傫���ꍇ
				sp = sd->status.max_sp - sd->status.sp; //SP��MSP-����SP�ɂ���
				sd->status.sp = sd->status.max_sp; //���݂�SP��MSP����
			}
			else //��SP+���݂�SP��MSP��菬�����ꍇ�͉�SP�����Z
				sd->status.sp += sp;
			clif_heal(sd->fd,SP_SP,sp); //SP�񕜃G�t�F�N�g�̕\��
			sd->canact_tick = tick + skill_delayfix(bl, skill_get_delay(SA_MAGICROD,bl->get_statusvalue1(SC_MAGICROD).integer())); //
		}
		clif_skill_nodamage(*bl,*bl,SA_MAGICROD,(unsigned short)bl->get_statusvalue1(SC_MAGICROD).integer(),1); //�}�W�b�N���b�h�G�t�F�N�g��\��
	}
//�}�W�b�N���b�h?�������܂�
	//Skotlex: Adjusted to the new system
	if(*src==BL_PET)
	{ // [Valaris]
		struct pet_data *pd = src->get_pd();
		if (pd->a_skill && pd->a_skill->div_ && pd->a_skill->id == skillid)
		{
			dmg.damage=battle_attr_fix(skilllv, skill_get_pl(skillid), status_get_element(bl) );
			dmg.damage2=0;
			dmg.div_= pd->a_skill->div_;
		}
	}

	damage = dmg.damage + dmg.damage2;

	if(lv==15)
		lv=-1;

	if( flag&0xff00 )
		type=(flag&0xff00)>>8;
	
	if( (damage <= 0 || damage < dmg.div_) &&	//������΂�����H��
		skillid != CH_PALMSTRIKE )				//Palm Strike is the only skill that will knockback even if it misses. [Skotlex]
		dmg.blewcount = 0;

	if(skillid == CR_GRANDCROSS||skillid == NPC_GRANDDARKNESS) {//�O�����h�N���X
		if(config.gx_disptype) dsrc = src;	// �G�_��?�W�������\��
		if( src == bl) type = 4;	// �����̓_��?�W��?�V�����Ȃ�
	}

//�g�p�҂�PC�̏ꍇ��?����������
	if(*src == BL_PC) {
		map_session_data *sd = (map_session_data *)src;
		nullpo_retr(0, sd);

		if(skillid == MO_TRIPLEATTACK)
		{
			int delay = 1000 - 4 * src->get_agi() - 2 *  src->get_dex();
			if (damage < bl->get_hp() &&
				sd->skill_check( MO_CHAINCOMBO) > 0)
				delay += 300 * config.combo_delay_rate / 100;
			status_change_start(src,SC_COMBO,MO_TRIPLEATTACK,skilllv,0,0,delay,0);
			sd->attackable_tick = sd->canmove_tick = tick + delay;
			clif_combo_delay(*src, delay);
		}
//�A�ŏ�(MO_CHAINCOMBO)��������
		else if(skillid == MO_CHAINCOMBO) {
			int delay = 1000 - 4 * src->get_agi() - 2 *  src->get_dex(); //��{�f�B���C�̌v�Z
			if(damage < bl->get_hp())
			{	//�_��?�W��?�ۂ�HP��菬�����ꍇ
				if(sd->skill_check( MO_COMBOFINISH) > 0 && sd->spiritball > 0) //�җ���(MO_COMBOFINISH)�擾��?���ێ�����+300ms
					delay += 300 * config.combo_delay_rate /100; //�ǉ��f�B���C��conf�ɂ�蒲��

					status_change_start(src,SC_COMBO,MO_CHAINCOMBO,skilllv,0,0,delay,0); //�R���{?�Ԃ�
			}
			sd->attackable_tick = sd->canmove_tick = tick + delay;
			clif_combo_delay(*src,delay); //�R���{�f�B���C�p�P�b�g�̑��M
		}
//�A�ŏ�(MO_CHAINCOMBO)�����܂�
//�җ���(MO_COMBOFINISH)��������
		else if(skillid == MO_COMBOFINISH) {
			int delay = 700 - 4 * src->get_agi() - 2 *  src->get_dex();
			if(damage < bl->get_hp())
			{	//���C���e����(MO_EXTREMITYFIST)�擾��?��4�ێ��������g��(MO_EXPLOSIONSPIRITS)?�Ԏ���+300ms
				//���Ռ�(CH_TIGERFIST)�擾����+300ms
				if((sd->skill_check( MO_EXTREMITYFIST) > 0 && sd->spiritball >= 4 && sd->has_status(SC_EXPLOSIONSPIRITS) ) ||
				(sd->skill_check( CH_TIGERFIST) > 0 && sd->spiritball > 0) ||
				(sd->skill_check( CH_CHAINCRUSH) > 0 && sd->spiritball > 1))
					delay += 300 * config.combo_delay_rate /100; //�ǉ��f�B���C��conf�ɂ�蒲��

				status_change_start(src,SC_COMBO,MO_COMBOFINISH,skilllv,0,0,delay,0); //�R���{?�Ԃ�
			}
			sd->attackable_tick = sd->canmove_tick = tick + delay;
			clif_combo_delay(*src,delay); //�R���{�f�B���C�p�P�b�g�̑��M
		}
//�җ���(MO_COMBOFINISH)�����܂�
//���Ռ�(CH_TIGERFIST)��������
		else if(skillid == CH_TIGERFIST) {
			int delay = 1000 - 4 * src->get_agi() - 2 *  src->get_dex();
			if(damage < bl->get_hp())
			{	//���C���e����(MO_EXTREMITYFIST)�擾��?��4�ێ��������g��(MO_EXPLOSIONSPIRITS)?�Ԏ���+300ms
				if((sd->skill_check( MO_EXTREMITYFIST) > 0 && sd->spiritball >= 3 && sd->has_status(SC_EXPLOSIONSPIRITS) ) ||
					(sd->skill_check( CH_CHAINCRUSH) > 0)) //�A����?(CH_CHAINCRUSH)�擾����+300ms
					delay += 300 * config.combo_delay_rate /100; //�ǉ��f�B���C��conf�ɂ�蒲��

				status_change_start(src,SC_COMBO,CH_TIGERFIST,skilllv,0,0,delay,0); //�R���{?�Ԃ�
			}
			sd->attackable_tick = sd->canmove_tick = tick + delay;
			clif_combo_delay(*src,delay); //�R���{�f�B���C�p�P�b�g�̑��M
		}
//���Ռ�(CH_TIGERFIST)�����܂�
//�A����?(CH_CHAINCRUSH)��������
		else if(skillid == CH_CHAINCRUSH) {
			int delay = 1000 - 4 * src->get_agi() - 2 *  src->get_dex();
			if(damage < bl->get_hp())
			{	//���C���e����(MO_EXTREMITYFIST)�擾��?��4�ێ��������g��(MO_EXPLOSIONSPIRITS)?�Ԏ���+300ms
				if(sd->skill_check( MO_EXTREMITYFIST) > 0 && sd->spiritball >= 1 && sd->has_status(SC_EXPLOSIONSPIRITS) )
					delay += 300 * config.combo_delay_rate /100; //�ǉ��f�B���C��conf�ɂ�蒲��

				status_change_start(src,SC_COMBO,CH_CHAINCRUSH,skilllv,0,0,delay,0); //�R���{?�Ԃ�
			}
			sd->attackable_tick = sd->canmove_tick = tick + delay;
			clif_combo_delay(*src,delay); //�R���{�f�B���C�p�P�b�g�̑��M
		}
//�A����?(CH_CHAINCRUSH)�����܂�
	}
//�g�p�҂�PC�̏ꍇ��?�������܂�
//����X�L���H��������

	if(attack_type&BF_MAGIC && damage > 0 && src != bl && src == dsrc)
	{
		map_session_data *tsd = bl->get_sd();
		if(tsd && tsd->magic_damage_return > 0)
		{
			rdamage += damage * tsd->magic_damage_return / 100;
			if(rdamage < 1) rdamage = 1;
		}
	}
	//Stop Here
	if(attack_type&BF_WEAPON && damage > 0 && src != bl && src == dsrc)
	{	//����X�L�����_��?�W���聕�g�p�҂�?�ێ҂��Ⴄ��src=dsrc
		if(dmg.flag&BF_SHORT)
		{	//�ߋ����U?���H��
			map_session_data *tsd = bl->get_sd();
			if(tsd)
			{	//?�ۂ�PC�̎�
				if(tsd->short_weapon_damage_return > 0)
				{ //�ߋ����U?���˕Ԃ��H��
					rdamage += damage * tsd->short_weapon_damage_return / 100;
					if(rdamage < 1) rdamage = 1;
				}
			}
			if(bl->has_status(SC_REFLECTSHIELD))
			{	//���t���N�g�V?���h��
				rdamage += damage * bl->get_statusvalue2(SC_REFLECTSHIELD).integer() / 100; //���˕Ԃ��v�Z
				if(rdamage < 1) rdamage = 1;
			}
		}
		else if(dmg.flag&BF_LONG)
		{	//�������U?���H��
			map_session_data *tsd = bl->get_sd();
			if(tsd)
			{ //?�ۂ�PC�̎�
				if(tsd->long_weapon_damage_return > 0)
				{	//�������U?���˕Ԃ��H��
					rdamage += damage * tsd->long_weapon_damage_return / 100;
					if(rdamage < 1) rdamage = 1;
				}
			}
		}
		if(rdamage > 0)
			clif_damage(*src,*src,tick, dmg.amotion,0,rdamage,1,4,0);
	}
//����X�L���H�����܂�

	switch(skillid){
	case AS_SPLASHER:
		clif_skill_damage(*dsrc,*bl,tick,dmg.amotion, dmg.dmotion, damage, dmg.div_, skillid, 0xFFFF, 5);
		break;
	case ASC_BREAKER:	// [celest]
		if (attack_type&BF_MAGIC) {	// only display damage for the 2nd attack
			if (damage + tmpdmg != 0)	// if both attacks missed, do not display a 2nd 'miss'
				clif_skill_damage(*dsrc, *bl, tick, dmg.amotion, dmg.dmotion, damage+tmpdmg, dmg.div_, skillid, skilllv, type);
			tmpdmg = 0;	// clear the temporary damage
		} else {
			if (damage == 0)	// if weapon attack missed, display the 'miss'
				clif_skill_damage(*dsrc, *bl, tick, dmg.amotion, dmg.dmotion, 0, dmg.div_, skillid, skilllv, type);
			tmpdmg = damage;	// store the temporary weapon damage
		}
		break;
	case NPC_SELFDESTRUCTION:
		if(*src==BL_PC)
			dmg.blewcount = 10;
		break;

	case KN_AUTOCOUNTER: //Skills that need be passed as a normal attack for the client to display correctly.
	case SN_SHARPSHOOTING:
		clif_damage(*src,*bl,tick,dmg.amotion,dmg.dmotion,damage,dmg.div_,dmg.type,dmg.damage2);
		break;
	default:
		clif_skill_damage(*dsrc,*bl,tick,dmg.amotion,dmg.dmotion, damage, dmg.div_, skillid, (lv!=0)?lv:skilllv, (skillid==0)? 5:type );
	}


	block_list::freeblock_lock();

	if(damage > 0 && dmg.flag&BF_SKILL && *bl==BL_PC && bl->skill_check(RG_PLAGIARISM) && !bl->has_status(SC_PRESERVE))
	{
		map_session_data *tsd = bl->get_sd();
		if (tsd && (!tsd->status.skill[skillid].id || tsd->status.skill[skillid].flag >= 13) &&
			skill_can_copy(*tsd,skillid) )
		{
			//?��?��ł���X�L��������ΊY?�X�L��������
			if (tsd->cloneskill_id && tsd->status.skill[tsd->cloneskill_id].flag == 13){

				tsd->status.skill[tsd->cloneskill_id].id = 0;
				tsd->status.skill[tsd->cloneskill_id].lv = 0;
				tsd->status.skill[tsd->cloneskill_id].flag = 0;
			}
			tsd->cloneskill_id = skillid;
			tsd->status.skill[skillid].id = skillid;
			tsd->status.skill[skillid].lv = skilllv;
			if ((lv = tsd->skill_check(RG_PLAGIARISM)) < skilllv)
				tsd->status.skill[skillid].lv = lv;
			tsd->status.skill[skillid].flag = 13;//cloneskill flag
			pc_setglobalreg(*tsd, "CLONE_SKILL", tsd->cloneskill_id);
			pc_setglobalreg(*tsd, "CLONE_SKILL_LV", tsd->status.skill[skillid].lv);
			clif_skillinfoblock(*tsd);

		}
	}

	// ?�ۂɃ_��?�W?�����s��
	if (skillid || flag) {
		if (attack_type&BF_WEAPON)
			battle_delay_damage(tick+dmg.amotion,*src,*bl,damage,0);
		else
			battle_damage(src,bl,damage,0);
	}
	if(skillid == RG_INTIMIDATE && damage > 0 && !(bl->get_mode()&0x20) && !maps[src->m].flag.gvg ) {
		int s_lv = src->get_lv(),t_lv = bl->get_lv();
		int rate = 50 + skilllv * 5;
		rate = rate + (s_lv - t_lv);
		if(rand()%100 < rate)
			skill_addtimerskill(src,tick + 800,bl->id,0,0,skillid,skilllv,0,flag);
	}

	// �_��?�W������Ȃ�ǉ�?�ʔ���
	if( bl->is_on_map() && !bl->is_dead() )
	{
		if(damage > 0)
			skill_additional_effect(src,bl,skillid,skilllv,attack_type,tick);

		// ������΂������Ƃ��̃p�P�b�g
		if (dmg.blewcount > 0 && *bl!=BL_SKILL && !maps[src->m].flag.gvg)
		{
			skill_blown(dsrc,bl,dmg.blewcount);
			clif_fixobject(*bl);
		}

		if( *bl==BL_MOB && src!=bl )
		{	// �X�L���g�p?����MOB�X�L��
			struct mob_data *md=bl->get_md();
			if(config.mob_changetarget_byskill == 1)
			{
				int target;
				target=md->target_id;
				if(*src == BL_PC)
					md->target_id=src->id;
				mobskill_use(*md,tick,MSC_SKILLUSED|(skillid<<16));
				md->target_id=target;
			}
			else
				mobskill_use(*md,tick,MSC_SKILLUSED|(skillid<<16));
		}
	}

	if(*src == BL_PC && dmg.flag&BF_WEAPON && src != bl && src == dsrc && damage > 0) {
		map_session_data *sd = (map_session_data *)src;
		int hp = 0,sp = 0;
		nullpo_retr(0, sd);
		if(sd->right_weapon.hp_drain_rate && sd->right_weapon.hp_drain_per > 0 && dmg.damage > 0 && rand()%100 < sd->right_weapon.hp_drain_rate) {
			hp += (dmg.damage * sd->right_weapon.hp_drain_per)/100;
			if(sd->right_weapon.hp_drain_rate > 0 && hp < 1) hp = 1;
			else if(sd->right_weapon.hp_drain_rate < 0 && hp > -1) hp = -1;
		}
		if(sd->left_weapon.hp_drain_rate && sd->left_weapon.hp_drain_per > 0 && dmg.damage2 > 0 && rand()%100 < sd->left_weapon.hp_drain_rate) {
			hp += (dmg.damage2 * sd->left_weapon.hp_drain_per)/100;
			if(sd->left_weapon.hp_drain_rate > 0 && hp < 1) hp = 1;
			else if(sd->left_weapon.hp_drain_rate < 0 && hp > -1) hp = -1;
		}
		if(sd->right_weapon.sp_drain_rate > 0 && sd->right_weapon.sp_drain_per > 0 && dmg.damage > 0 && rand()%100 < sd->right_weapon.sp_drain_rate) {
			sp += (dmg.damage * sd->right_weapon.sp_drain_per)/100;
			if(sd->right_weapon.sp_drain_rate > 0 && sp < 1) sp = 1;
			else if(sd->right_weapon.sp_drain_rate < 0 && sp > -1) sp = -1;
		}
		if(sd->left_weapon.sp_drain_rate > 0 && sd->left_weapon.sp_drain_per > 0 && dmg.damage2 > 0 && rand()%100 < sd->left_weapon.sp_drain_rate) {
			sp += (dmg.damage2 * sd->left_weapon.sp_drain_per)/100;
			if(sd->left_weapon.sp_drain_rate > 0 && sp < 1) sp = 1;
			else if(sd->left_weapon.sp_drain_rate < 0 && sp > -1) sp = -1;
		}
		if(hp || sp)
			sd->heal(hp,sp);
		if (sd->sp_drain_type && *bl == BL_PC)
			battle_heal(NULL,bl,0,-sp,0);
	}

	if ((skillid || flag) && rdamage>0) {
		if (attack_type&BF_WEAPON)
			battle_delay_damage(tick+dmg.amotion,*bl,*src,rdamage,0);
		else
			battle_damage(bl,src,rdamage,0);
	}

	if(attack_type&BF_WEAPON && bl->has_status(SC_AUTOCOUNTER) && bl->get_statusvalue4(SC_AUTOCOUNTER).integer() > 0) {
		if((uint32)bl->get_statusvalue3(SC_AUTOCOUNTER).integer() == dsrc->id)
			battle_weapon_attack(bl,dsrc,tick,0x8000|bl->get_statusvalue1(SC_AUTOCOUNTER).integer());
		status_change_end(bl,SC_AUTOCOUNTER,-1);
	}
	
	if( (//skillid == MG_NAPALMBEAT || skillid == MG_SOULSTRIKE ||
		 //skillid == MG_FIREBALL || skillid == MG_FROSTDIVER ||
		 skillid == MG_COLDBOLT || skillid == MG_FIREBOLT || skillid == MG_LIGHTNINGBOLT ) &&
		src->has_status(SC_DOUBLECAST) &&
		rand() % 100 < 40+10*src->get_statusvalue1(SC_DOUBLECAST).integer())
	{
		if (!(flag & 1))
			skill_castend_delay(*src, *bl, skillid, skilllv, tick + dmg.div_*dmg.amotion, flag|1);
	}

	block_list::freeblock_unlock();

	return (dmg.damage+dmg.damage2);	// ?�_����Ԃ�
}

/*==========================================
 * �X�L����?�U?�p(map_foreachinarea����Ă΂��)
 * flag�ɂ��āF16�i?���m�F
 * MSB <- 00fTffff ->LSB
 *	T	=�^?�Q�b�g�I?�p(BCT_*)
 *  ffff=���R�Ɏg�p�\
 *  0	=�\��B0�ɌŒ�
 *------------------------------------------
 */
static uint32 skill_area_temp[8];	// �ꎞ??�B�K�v�Ȃ�g���B

typedef int (*SkillFunc)(block_list *,block_list *,unsigned short,unsigned short,unsigned long,int);


class CSkillArea : public CMapProcessor
{
	block_list &src;
	unsigned short skillid;
	unsigned short skilllv;
	unsigned long tick;
	int flag;
	SkillFunc func;
public:
	CSkillArea(block_list &s,unsigned short sid,unsigned short slv,unsigned long t,int f,SkillFunc fc)
		:src(s),skillid(sid),skilllv(slv),tick(t),flag(f),func(fc)
	{}
	~CSkillArea()	{}
	virtual int process(block_list& bl) const
	{
		if(bl!=BL_PC && bl!=BL_MOB && bl!=BL_SKILL)
			return 0;
		if(battle_check_target(&src,&bl,flag) > 0)
			func(&src,&bl,skillid,skilllv,tick,flag);
		return 0;
	}
};

class CSkillCheckUnitrange : public CMapProcessor
{
	ICL_EMPTY_COPYCONSTRUCTOR(CSkillCheckUnitrange)
	unsigned short skillid;
public:
	CSkillCheckUnitrange(unsigned short sid)
		: skillid(sid)	{}
	~CSkillCheckUnitrange()	{}
	virtual int process(block_list& bl) const
	{
		skill_unit *unit;
		if( bl.is_on_map() && (unit=bl.get_sk()) && unit->alive )
		{
			int unit_id = (unit->group)?unit->group->unit_id:0;
			if (skillid==MG_SAFETYWALL || skillid==AL_PNEUMA)
			{
				if(unit_id != UNT_SAFETYWALL && unit_id != UNT_PNEUMA)
					return 0;
			}
			else if (skillid==AL_WARP)
			{
				if ((unit_id<0x8f || unit_id>0x99) && unit_id!=UNT_VENOMDUST)
					return 0;
			}
			else if ((skillid>=HT_SKIDTRAP && skillid<=HT_CLAYMORETRAP) || skillid==HT_TALKIEBOX)
			{
				if ((unit_id<0x8f || unit_id>0x99) && unit_id!=UNT_VENOMDUST)
					return 0;
			}
			else if (skillid==WZ_FIREPILLAR)
			{
				if (unit_id!=UNT_FIREPILLAR_HIDDEN)
					return 0;
			}
			else if (skillid==HP_BASILICA)
			{
				if ((unit_id<0x8f || unit_id>0x99) && unit_id!=UNT_VENOMDUST && unit_id!=0x83)
					return 0;
			}
			else if (skillid==HW_GRAVITATION)
			{
				if (unit_id!=0xb8)
					return 0;
			}
			else if (skillid==AM_DEMONSTRATION)
			{
				if (unit_id!=UNT_DEMONSTRATION)
					return 0;
			}
			else
				return 0;
			return 1;
		}
		return 0;
	}
};
int skill_check_unit_range(int m,int x,int y,unsigned short skillid,unsigned short skilllv)
{
//	int c = 0;
	int range = skill_get_unit_range(skillid);
	int layout_type = skill_get_unit_layout_type(skillid,skilllv);
	if (layout_type==-1 || layout_type>MAX_SQUARE_LAYOUT) {
		ShowMessage("skill_check_unit_range: unsupported layout type %d for skill %d\n",layout_type,skillid);
		return 0;
	}
	// �Ƃ肠���������`�̃��j�b�g���C�A�E�g�̂ݑΉ�
	range += layout_type;
	return maps[m].foreachinarea( CSkillCheckUnitrange(skillid),x,y,range,BL_SKILL);
}

class CSkillCheckUnitrange2 : public CMapProcessor
{
	ICL_EMPTY_COPYCONSTRUCTOR(CSkillCheckUnitrange2)
	unsigned short skillid;
public:
	CSkillCheckUnitrange2(unsigned short sid)
		: skillid(sid)	{}
	~CSkillCheckUnitrange2()	{}
	virtual int process(block_list& bl) const
	{
		if( !bl.is_on_map() || (bl != BL_PC && bl != BL_MOB))
			return 0;

		if( bl.is_dead() )
			return 0;

		if (skillid==HP_BASILICA && bl==BL_PC)
			return 0;

		if (skillid==AM_DEMONSTRATION && bl==BL_MOB && bl.get_md()->class_ == MOBID_EMPERIUM)
			return 0; //Allow casting Bomb/Demonstration Right under emperium
		return 1;
	}
};

int skill_check_unit_range2(int m,int x,int y,unsigned short skillid, unsigned short skilllv, object_t type)
{
	int range;
	switch (skillid)
	{	// to be expanded later
	case WZ_ICEWALL:
		range = 2;
		break;
	default:
		{
			int layout_type = skill_get_unit_layout_type(skillid,skilllv);
			if (layout_type==-1 || layout_type>MAX_SQUARE_LAYOUT) {
				ShowMessage("skill_check_unit_range2: unsupported layout type %d for skill %d\n",layout_type,skillid);
				return 0;
			}
			// �Ƃ肠���������`�̃��j�b�g���C�A�E�g�̂ݑΉ�
			range = skill_get_unit_range(skillid) + layout_type;
		}
		break;
	}

	// if the caster is a monster/NPC, only check for players
	// otherwise just check everything
	if( type == BL_PC )
		type = BL_ALL;
	else 
		type = BL_PC;

	return maps[m].foreachinarea( CSkillCheckUnitrange2(skillid), x, y, range, type);
}


int CSkillGuildaura::process(block_list &bl) const
{
	map_session_data &sd=(map_session_data &)bl;
	if( bl==BL_PC && sd.status.guild_id == gid && flag > 0 )
	{
		if( !sd.has_status(SC_GUILDAURA) )
		{	// start skill
			status_change_start(&sd, SC_GUILDAURA, 1, id, 0, flag, 0, 0);
		}
		else if (sd.get_statusvalue4(SC_GUILDAURA).integer() != flag)
		{	// modify skill
			sd.get_statusvalue4(SC_GUILDAURA).integer() = flag;
			status_calc_pc (sd, 0);
		}
		// else ok
	}

	return 0;
}
/*=========================================================================
 * ��?�X�L���g�p?����������������
 */
// ?�ۂ�?���J�E���g����B�iskill_area_temp[0]�����������Ă������Ɓj
int skill_area_sub_count(block_list *src,block_list *target,unsigned short skillid,unsigned short skilllv,unsigned long tick,int flag)
{
	if(skill_area_temp[0] < 0xffff)
		skill_area_temp[0]++;
	return 0;
}

int skill_count_water(block_list &src,int range)
{
	int xi,yi,x,y,cnt = 0;
	struct skill_unit *unit;
	for(xi=-range;xi<range;++xi)
	for(yi=-range;yi<range;++yi)
	{
		x = src.x+xi;
		y = src.y+yi;
		if(  maps[src.m].is_water(x, y) ||
			(maps[src.m].flag.rain==1 && config.rainy_waterball && rand()%2) ) // half as strong on rain
		{
			++cnt;
		}
		else
		{
			unit = block_list::skillunit_oncell(src, x, y, SA_DELUGE,NULL);
			if (unit) {
				++cnt;
				skill_delunit(unit);
			}
		}
	}
	return cnt;
}
/*==========================================
 *
 *------------------------------------------
 */
int skill_timerskill(int tid, unsigned long tick, int id, basics::numptr data)
{
	map_session_data *sd = NULL;
	struct mob_data *md = NULL;
	struct pet_data *pd = NULL;
	block_list *src = block_list::from_blid(id),*target;
	struct skill_timerskill *skl = NULL;
	int range;

	nullpo_retr(0, src);

	if(data.num<0 || data.num >=MAX_SKILLTIMERSKILL)
		return 0;

	if(*src == BL_PC) {
		sd = src->get_sd();
		skl = &sd->skilltimerskill[data.num];
	}
	else if(*src == BL_MOB) {
		md = src->get_md();
		skl = &md->skilltimerskill[data.num];
	}
	else if(*src == BL_PET) { // [Valaris]
		pd = src->get_pd();
		skl = &pd->skilltimerskill[data.num];
	}
	else
		return 0;

	if(tid != skl->timer)
		return 0;

	skl->timer = -1;

	if( !src->is_on_map() )
		return 0;

	if(skl->target_id)
	{
		block_list tbl;
		target = block_list::from_blid(skl->target_id);
		if(skl->skill_id == RG_INTIMIDATE)
		{
			if(target == NULL)
			{	//���������ĂȂ��̂ɃA�h���X�˂�?��ł����̂��ȁH
				target = &tbl; 
				target->m = src->m;
			}
		}
		if(target == NULL)
			return 0;
		if( !target->is_on_map() && skl->skill_id != RG_INTIMIDATE)
			return 0;
		if(src->m != target->m)
			return 0;
		if(sd && sd->is_dead())
			return 0;
		if(*target == BL_PC && target->is_dead() && skl->skill_id != RG_INTIMIDATE)
			return 0;

		switch(skl->skill_id)
		{
			case TF_BACKSLIDING:
				clif_skill_nodamage(*src,*src,skl->skill_id,skl->skill_lv,1);
				break;
			case RG_INTIMIDATE:
				if(sd && !maps[src->m].flag.noteleport) {
					int i,j;
					int x=0,y=0;
					pc_randomwarp(*sd,3);
					for(i=0;i<16;++i) {
						j = rand()%8;
						x = sd->block_list::x + dirx[j];
						y = sd->block_list::y + diry[j];
						if( maps[sd->block_list::m].is_passable(x,y) )
							break;
					}
					if(i >= 16) {
						x = sd->block_list::x;
						y = sd->block_list::y;
					}
					if( target->is_on_map() )
					{
						if(*target== BL_PC && !((map_session_data *)target)->is_dead())
							pc_setpos(*((map_session_data *)target),maps[sd->block_list::m].mapname,x,y,3);
						else if(*target== BL_MOB)
							mob_warp(*((struct mob_data *)target),-1,x,y,3);
					}
				}
				else if(md && !maps[src->m].flag.monster_noteleport) {
					int i,j;
					int x=0,y=0;
					mob_warp(*md,-1,-1,-1,3);
					for(i=0;i<16;++i) {
						j = rand()%8;
						x = md->block_list::x + dirx[j];
						y = md->block_list::y + diry[j];
						if( maps[md->block_list::m].is_passable(x,y) )
							break;
					}
					if(i >= 16) {
						x = md->block_list::x;
						y = md->block_list::y;
					}
					if( target->is_on_map() )
					{
						if(*target== BL_PC && !((map_session_data *)target)->is_dead())
							pc_setpos(*((map_session_data *)target),maps[md->block_list::m].mapname,x,y,3);
						else if(*target== BL_MOB)
							mob_warp(*((struct mob_data *)target),-1,x,y,3);
					}
				}
				break;

			case BA_FROSTJOKE:			// �����W��?�N
			case DC_SCREAM:				// �X�N��?��
				range=config.area_size;		//���E�S?

				maps[src->m].foreachinarea( CSkillFrostjoke(*src, skl->skill_id, skl->skill_lv, tick), src->x, src->y, range, BL_ALL);
				break;

			case WZ_WATERBALL:
				if (skl->type>1) {
					skl->timer = 0;	// skill_addtimerskill�Ŏg�p����Ȃ��悤��
					skill_addtimerskill(src,tick+150,target->id,0,0,skl->skill_id,skl->skill_lv,skl->type-1,skl->flag);
					skl->timer = -1;
				}
				skill_attack(BF_MAGIC,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				if (skl->type <= 1) {	// partial fix: it still doesn't end if the target dies
					// should put outside of the switch, but since this is the only
					// mage targetted spell for now,
					if( src->has_status(SC_MAGICPOWER) )	//�}�W�b�N�p��?��?�ʏI��
						status_change_end(src,SC_MAGICPOWER,-1);
				}
				break;
			default:
				skill_attack(skl->type,src,src,target,skl->skill_id,skl->skill_lv,tick,skl->flag);
				break;
		}
	}
	else {
		if(src->m != skl->map)
			return 0;
		switch(skl->skill_id) {
			case WZ_METEOR:
				if(skl->type >= 0) {
					skill_unitsetting(src,skl->skill_id,skl->skill_lv,(skl->type>>16)&0xFFFF,skl->type&0xFFFF,0);
					clif_skill_poseffect(*src,skl->skill_id,skl->skill_lv,skl->x,skl->y,tick);
				}
				else
					skill_unitsetting(src,skl->skill_id,skl->skill_lv,skl->x,skl->y,0);
				break;
		}
	}

	return 0;
}

/*==========================================
 *
 *------------------------------------------
 */
int skill_addtimerskill(block_list *src,unsigned long tick,int target,int x,int y,unsigned short skill_id,unsigned short skill_lv,int type,int flag)
{
	int i;

	nullpo_retr(1, src);

	if(*src == BL_PC) {
		map_session_data *sd = (map_session_data *)src;
		nullpo_retr(1, sd);
		for(i=0;i<MAX_SKILLTIMERSKILL;++i) {
			if(sd->skilltimerskill[i].timer == -1) {

				sd->skilltimerskill[i].timer = add_timer(tick, skill_timerskill, src->id, i);
				sd->skilltimerskill[i].src_id = src->id;
				sd->skilltimerskill[i].target_id = target;
				sd->skilltimerskill[i].skill_id = skill_id;
				sd->skilltimerskill[i].skill_lv = skill_lv;
				sd->skilltimerskill[i].map = src->m;
				sd->skilltimerskill[i].x = x;
				sd->skilltimerskill[i].y = y;
				sd->skilltimerskill[i].type = type;
				sd->skilltimerskill[i].flag = flag;

				return 0;
			}
		}
		return 1;
	}
	else if(*src == BL_MOB) {
		struct mob_data *md = (struct mob_data *)src;
		nullpo_retr(1, md);
		for(i=0;i<MAX_MOBSKILLTIMERSKILL;++i) {
			if(md->skilltimerskill[i].timer == -1) {
				md->skilltimerskill[i].timer = add_timer(tick, skill_timerskill, src->id, i);
				md->skilltimerskill[i].src_id = src->id;
				md->skilltimerskill[i].target_id = target;
				md->skilltimerskill[i].skill_id = skill_id;
				md->skilltimerskill[i].skill_lv = skill_lv;
				md->skilltimerskill[i].map = src->m;
				md->skilltimerskill[i].x = x;
				md->skilltimerskill[i].y = y;
				md->skilltimerskill[i].type = type;
				md->skilltimerskill[i].flag = flag;

				return 0;
			}
		}
		return 1;
	}
	else if(*src == BL_PET) { // [Valaris]
		struct pet_data *pd = (struct pet_data *)src;
		nullpo_retr(1, pd);
		for(i=0;i<MAX_MOBSKILLTIMERSKILL;++i) {
			if(pd->skilltimerskill[i].timer == -1) {
				pd->skilltimerskill[i].timer = add_timer(tick, skill_timerskill, src->id, i);
				pd->skilltimerskill[i].src_id = src->id;
				pd->skilltimerskill[i].target_id = target;
				pd->skilltimerskill[i].skill_id = skill_id;
				pd->skilltimerskill[i].skill_lv = skill_lv;
				pd->skilltimerskill[i].map = src->m;
				pd->skilltimerskill[i].x = x;
				pd->skilltimerskill[i].y = y;
				pd->skilltimerskill[i].type = type;
				pd->skilltimerskill[i].flag = flag;

				return 0;
			}
		}
		return 1;
	}
	return 1;
}

/*==========================================
 *
 *------------------------------------------
 */
int skill_cleartimerskill(block_list *src)
{
	int i;

	nullpo_retr(0, src);

	if(*src == BL_PC)
	{
		map_session_data *sd = (map_session_data *)src;
		nullpo_retr(0, sd);

		for(i=0;i<MAX_SKILLTIMERSKILL;++i) {
			if(sd->skilltimerskill[i].timer != -1) {
				delete_timer(sd->skilltimerskill[i].timer, skill_timerskill);
				sd->skilltimerskill[i].timer = -1;
			}
		}
	}
	else if(*src == BL_MOB)
	{
		struct mob_data *md = (struct mob_data *)src;
		nullpo_retr(0, md);
		for(i=0;i<MAX_MOBSKILLTIMERSKILL;++i) {
			if(md->skilltimerskill[i].timer != -1) {
				delete_timer(md->skilltimerskill[i].timer, skill_timerskill);
				md->skilltimerskill[i].timer = -1;
			}
		}
	}
	else if(*src == BL_PET)
	{
		pet_data *pd = (pet_data *)src;
		nullpo_retr(1, pd);
		for(i=0;i<MAX_MOBSKILLTIMERSKILL;++i) {
			if(pd->skilltimerskill[i].timer != -1) {
				delete_timer(pd->skilltimerskill[i].timer, skill_timerskill);
				pd->skilltimerskill[i].timer = -1;
			}
		}
	}
	return 0;
}
int skill_castend_delay_sub (int tid, unsigned long tick, int id, basics::numptr data)
{
	castend_delay *dat = (struct castend_delay *)data.ptr;
	if(dat)
	{
		block_list *target = block_list::from_blid(dat->target_id);
		if (target && (uint32)id == dat->src.id && target->is_on_map() )
			skill_castend_damage_id(&dat->src, target, dat->skill_id, dat->skill_lv, tick, dat->flag);
		delete dat;
		get_timer(tid)->data=0;
	}
	return 0;
}
int skill_castend_delay(block_list& src, block_list &bl, unsigned short skillid, unsigned short skilllv, unsigned long tick, int flag)
{
	castend_delay *dat = new castend_delay(src, bl.id, skillid, skilllv, flag);
	add_timer (tick, skill_castend_delay_sub, src.id, basics::numptr(dat), false);
	return 0;
}

/* ��?�X�L���g�p?�������������܂�
 * -------------------------------------------------------------------------
 */

/*==========================================
 * �X�L���g�p�i�r�������AID�w��U?�n�j
 * �i�X�p�Q�b�e�B�Ɍ����ĂP?�O�i�I(�_���|)�j
 *------------------------------------------
 */
int skill_castend_damage_id( block_list* src, block_list *bl, unsigned short skillid, unsigned short skilllv, unsigned long tick, int flag)
{
	map_session_data *sd = NULL, *tsd = NULL;

	if (skillid > 0 && skilllv <= 0) return 0;

	nullpo_retr(1, src);
	nullpo_retr(1, bl);	

	if (*src == BL_PC) {
		nullpo_retr(1, sd = (map_session_data *)src);
	}
	if (sd && sd->is_dead())
		return 1;

	if( !bl->is_on_map() )
		return 1;
	if (*bl == BL_PC) {
		nullpo_retr(1, tsd = (map_session_data *)bl);
	}
	if (tsd && tsd->is_dead())
		return 1;

	if ((skillid == CR_GRANDCROSS || skillid == NPC_GRANDDARKNESS) && src != bl)
		bl = src;
	
	block_list::freeblock_lock();

	switch(skillid)
	{
	// ����U?�n�X�L��
	case SM_BASH:			// �o�b�V��
	case MC_MAMMONITE:		// ���}?�i�C�g
	case AC_DOUBLE:			// �_�u���X�g���C�t�B���O
	case AS_SONICBLOW:		// �\�j�b�N�u��?
	case KN_PIERCE:			// �s�A?�X
	case KN_SPEARBOOMERANG:	// �X�s�A�u?������
	case KN_BRANDISHSPEAR:		// �u�����f�B�b�V���X�s�A
	case TF_POISON:			// �C���x�i��
	case TF_SPRINKLESAND:	// ���܂�
	case AC_CHARGEARROW:	// �`��?�W�A��?
	case RG_RAID:		// �T�v���C�Y�A�^�b�N
	case RG_INTIMIDATE:		// �C���e�B�~�f�C�g
	case BA_MUSICALSTRIKE:	// �~��?�W�J���X�g���C�N
	case DC_THROWARROW:		// ��?��
	case BA_DISSONANCE:		// �s���a��
	case NPC_DARKCROSS:
	case CR_HOLYCROSS:		// �z?��?�N���X
	case CR_SHIELDCHARGE:
	case CR_SHIELDBOOMERANG:
	// �ȉ�MOB?�p
	// ??�U?�ASP�����U?�A�������U?�A�h�䖳���U?�A���i�U?
	case NPC_PIERCINGATT:
	case NPC_MENTALBREAKER:
	case NPC_RANGEATTACK:
	case NPC_CRITICALSLASH:
	case NPC_COMBOATTACK:
	// �K���U?�A�ōU?�A��?�U?�A��?�U?�A�X�^���U?
	case NPC_GUIDEDATTACK:
	case NPC_POISON:
	case NPC_BLINDATTACK:
	case NPC_SILENCEATTACK:
	case NPC_STUNATTACK:
	// �Ή��U?�A�􂢍U?�A�����U?�A�����_��ATK�U?
	case NPC_PETRIFYATTACK:
	case NPC_CURSEATTACK:
	case NPC_SLEEPATTACK:
	case NPC_RANDOMATTACK:
	// ��?���U?�A�n?���U?�A��?���U?�A��?���U?
	case NPC_WATERATTACK:
	case NPC_GROUNDATTACK:
	case NPC_FIREATTACK:
	case NPC_WINDATTACK:
	// ��?���U?�A��?���U?�A��?���U?�A�O?���U?�ASP�����U?
	case NPC_POISONATTACK:
	case NPC_HOLYATTACK:
	case NPC_DARKNESSATTACK:
	case NPC_TELEKINESISATTACK:
	case NPC_UNDEADATTACK:
	case NPC_BREAKARMOR:
	case NPC_BREAKWEAPON:
	case NPC_BREAKHELM:
	case NPC_BREAKSHIELD:
	case LK_AURABLADE:		// �I?���u��?�h
	case LK_SPIRALPIERCE:	// �X�p�C�����s�A?�X
	case LK_HEADCRUSH:	// �w�b�h�N���b�V��
	case LK_JOINTBEAT:	// �W���C���g�r?�g
	case CG_ARROWVULCAN:			// �A��?�o���J��
	case HW_MAGICCRASHER:		// �}�W�b�N�N���b�V��?
	case ASC_METEORASSAULT:	// ���e�I�A�T���g
	case ITM_TOMAHAWK:
	case MO_TRIPLEATTACK:
	case MO_COMBOFINISH:	// �җ���
	case CH_CHAINCRUSH:		// �A����?
	case CH_PALMSTRIKE:		// �ҌՍd�h�R
	case PA_SHIELDCHAIN:	// Shield Chain
	case TK_JUMPKICK:	// Taekwon Jump kick waiting to be coded [Dralnu]
		skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;
	case TK_STORMKICK: // Taekwon kicks [Dralnu]
	{
		if( src->has_status(SC_STORMKICK) )
		{
			maps[src->m].foreachinarea( CSkillAttackArea(BF_WEAPON, *src, *src, skillid, skilllv, tick, flag, BCT_ENEMY), src->x, src->y, 2, BL_ALL);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		status_change_end(src, SC_STORMKICK, -1);
		break;
	}
	case TK_DOWNKICK:
	{
		if( src->has_status(SC_DOWNKICK) )
		{
			bl = block_list::from_blid(src->get_statusvalue2(SC_DOWNKICK).integer());
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		status_change_end(src, SC_DOWNKICK, -1);
		break;
	}
	case TK_TURNKICK:
	{
		if( src->has_status(SC_TURNKICK) )
		{
			bl = block_list::from_blid(src->get_statusvalue2(SC_TURNKICK).integer());
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		status_change_end(src, SC_TURNKICK, -1);
		break;
	}
	case TK_COUNTER:
	{
		if( src->has_status(SC_COUNTER) )
		{
			bl = block_list::from_blid(src->get_statusvalue2(SC_COUNTER).integer());
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		status_change_end(src, SC_COUNTER, -1);
		break;
	}
	
	case WS_CARTTERMINATION:	// Cart Termination
		if( src->has_status(SC_CARTBOOST) )
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		else if (sd) sd->skill_failed(skillid);
		break;

	case ASC_BREAKER:				// �\�E���u��?�J?	// [DracoRPG]
		// separate weapon and magic attacks
		skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;
	
	case SN_SHARPSHOOTING:			// �V��?�v�V��?�e�B���O

		maps[src->m].foreachinpath(
			CSkillAttackArea(BF_WEAPON,*src,*src,skillid,skilllv,tick,flag,BCT_ENEMY),
			src->x,src->y,			// source xy
			bl->x,bl->y,			// target xy
			2,BL_ALL				// range, type
			);
		break;

	case NPC_DARKBREATH:
		clif_emotion(*src,7);
		skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag);
		break;

	case MO_INVESTIGATE:	// ?��
		skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		if( src->has_status(SC_BLADESTOP) )
			status_change_end(src,SC_BLADESTOP,-1);
		break;

	case PA_SACRIFICE:				// sacrifice new style
	case SN_FALCONASSAULT:			// �t�@���R���A�T���g 
	case PA_PRESSURE:				// �v���b�V��? 
	case CR_ACIDDEMONSTRATION:
		skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,flag);
		break;

	case RG_BACKSTAP:		// �o�b�N�X�^�u
		{
			dir_t dir = src->get_direction(*bl);
			dir_t t_dir = bl->get_dir();
			int dist = distance(*src, *bl);
			if ((dist > 0 && is_same_direction(dir, t_dir)) || *bl == BL_SKILL) {
				if (src->has_status(SC_HIDING) )
					status_change_end(src, SC_HIDING, -1);	// �n�C�f�B���O����
				skill_attack(BF_WEAPON, src, src, bl, skillid, skilllv, tick, flag);
				dir = (dir < 4) ? (dir_t)(dir+4) : (dir_t)(dir-4); // change direction [Celest]
				if (tsd)
					tsd->dir = dir;
				else if (*bl == BL_MOB) {
					struct mob_data *tmd = (struct mob_data *)bl;
					if (tmd) tmd->dir = dir;
				}
				clif_changed_dir(*bl);
			}
			else if (sd)
				sd->skill_failed(sd->skillid);
		}
		break;

	case AM_ACIDTERROR:		// �A�V�b�h�e��?
		skill_attack(BF_WEAPON, src, src, bl, skillid, skilllv, tick, flag);
		if (tsd && (size_t)rand()%100 < skill_get_time(skillid,skilllv) * config.equip_skill_break_rate/100) {
			if( pc_breakarmor(*tsd) )
				clif_emotion(*bl, 23);
		}
		break;

	case MO_FINGEROFFENSIVE:	// �w?
		{
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			if (config.finger_offensive_type && sd) {
				int i;
				for (i = 1; i < sd->spiritball_old; ++i)
					skill_addtimerskill(src, tick + i * 200, bl->id, 0, 0, skillid, skilllv, BF_WEAPON, flag);
				sd->canmove_tick = tick + (sd->spiritball_old - 1) * 200;
			}
			if( src->has_status(SC_BLADESTOP) )
				status_change_end(src,SC_BLADESTOP,-1);
		}
		break;

	case MO_CHAINCOMBO:		// �A�ŏ�
		{
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			if( src->has_status(SC_BLADESTOP) )
				status_change_end(src,SC_BLADESTOP,-1);
		}
		break;

	case CH_TIGERFIST:		// ���Ռ�
		if (tsd && !(maps[bl->m].flag.gvg || maps[bl->m].flag.pvp)) {
			block_list::freeblock_unlock();
			return 1;
		}
		skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
		break;

	case MO_EXTREMITYFIST:	// ���C���e�P��
		{
			if(sd)
			{
				int dx,dy;

				dx = bl->x - sd->block_list::x;
				dy = bl->y - sd->block_list::y;
				if(dx > 0) ++dx;
				else if(dx < 0) --dx;
				if (dy > 0) ++dy;
				else if(dy < 0) --dy;
				if(dx == 0 && dy == 0) ++dx;
				if( !walkpath_data::is_possible(src->m,sd->block_list::x,sd->block_list::y,sd->block_list::x+dx,sd->block_list::y+dy,1) )
				{
					dx = bl->x - sd->block_list::x;
					dy = bl->y - sd->block_list::y;
					if( !walkpath_data::is_possible(src->m,sd->block_list::x,sd->block_list::y,sd->block_list::x+dx,sd->block_list::y+dy,1) )
					{
						sd->skill_failed(sd->skillid);
						break;
					}
				}
				sd->walktarget.x = sd->block_list::x + dx;
				sd->walktarget.y = sd->block_list::y + dy;
				skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
				clif_moveobject(*sd);
				if(dx < 0) dx = -dx;
				if(dy < 0) dy = -dy;
				sd->attackable_tick = sd->canmove_tick = tick + 100 + sd->speed * ((dx > dy)? dx:dy);
				if(sd->canact_tick < sd->canmove_tick)
					sd->canact_tick = sd->canmove_tick;
				sd->movepos(sd->walktarget.x,sd->walktarget.y);
				status_change_end(sd,SC_COMBO,-1);
			}
			else
				skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,flag);
			status_change_end(src, SC_EXPLOSIONSPIRITS, -1);
			if( src->has_status(SC_BLADESTOP) )
				status_change_end(src,SC_BLADESTOP,-1);
		}
		break;

	// ����n��?�U?�X�L��
	case AC_SHOWER:			// �A��?�V����?
	case AS_GRIMTOOTH:		// �O�����g�D?�X
	case MC_CARTREVOLUTION:	// �J?�g�����H����?�V����
	case NPC_SPLASHATTACK:	// �X�v���b�V���A�^�b�N
	case AS_SPLASHER:	// [Valaris]
		if(flag&1){
			// �ʂɃ_��?�W��?����
			if(bl->id!=skill_area_temp[1]){
				skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,
					0x0500);				
			}
		} else {
			int ar = 1;
			int x = bl->x, y = bl->y;
			switch (skillid) {
				case AC_SHOWER:
					ar=2;
					break;
				case NPC_SPLASHATTACK:
					ar=3;
					break;
			}

			skill_area_temp[1]=bl->id;
			skill_area_temp[2]=x;
			skill_area_temp[3]=y;
			// �܂��^?�Q�b�g�ɍU?��������
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
			// ���̌�^?�Q�b�g�ȊO�̔�??�̓G�S?��?�����s��

			maps[bl->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY|1,skill_castend_damage_id), x,y,ar,BL_ALL);
		}
		break;

	case SM_MAGNUM:			// �}�O�i���u���C�N [celest]
		if(flag&1 && bl->id != skill_area_temp[1]){
			int dist = bl->get_distance(skill_area_temp[2], skill_area_temp[3]);
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,
				0x0500|dist);
		} else {
			skill_area_temp[1]=src->id;
			skill_area_temp[2]=src->x;
			skill_area_temp[3]=src->y;
			maps[src->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY|1, skill_castend_damage_id),
				src->x, src->y, 2, BL_ALL);
			clif_skill_nodamage (*src,*src,skillid,skilllv,1);
			status_change_start (src,SC_WATK_ELEMENT,3,10,0,0,10000,0); //Initiate 10% of your damage becomes fire element.
		}
		break;

	case KN_BOWLINGBASH:	// �{�E�����O�o�b�V�� 
		if(flag&1)
		{	// �ʂɃ_��?�W��?���� 
			if(bl->id!=skill_area_temp[1])
				skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500);
		}
		else
		{	// ���l���畷���������Ȃ̂ŊԈ���Ă�\���偕?����?���������� 
			int i,c;
			// �܂��^�[�Q�b�g�ɍU���������� 
			if (!skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0))
				break;
			c = skill_get_blewcount(skillid,skilllv);
			if(maps[bl->m].flag.gvg) c = 0;
			for(i=0;i<c;++i)
			{
				skill_blown(src,bl,1);
				clif_fixobject(*bl);
				skill_area_temp[0]=0;
				maps[bl->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY, skill_area_sub_count),
					bl->x, bl->y, 1, BL_ALL);
				skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
				if(skill_area_temp[0]>1) break;
			}
			skill_area_temp[1]=bl->id;
			// ���̌�^?�Q�b�g�ȊO�̔�??�̓G�S?��?�����s�� 

			maps[bl->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY|1, skill_castend_damage_id),
				bl->x, bl->y, 1, BL_ALL);
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		}
		break;
	
	case KN_SPEARSTAB:		// �X�s�A�X�^�u
		if(flag&1){
			// �ʂɃ_���[�W��^����
			if(bl->id==skill_area_temp[1])
				break;
			if( skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0x0500) &&
				!(maps[bl->m].flag.gvg || bl->get_mexp()) )
				skill_blown(src,bl,skill_area_temp[2]);
		} else {
			int x=bl->x,y=bl->y,i;
			dir_t dir;
			// �܂��^�[�Q�b�g�ɍU����������
			dir = bl->get_direction(*src);
			skill_area_temp[1] = bl->id;
			skill_area_temp[2] = skill_get_blewcount(skillid,skilllv)|dir<<20;
			if( skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0) &&
				!(maps[bl->m].flag.gvg || bl->get_mexp()) )
				skill_blown(src,bl,skill_area_temp[2]);
			for (i=0;i<4;++i)
			{
				maps[bl->m].foreachincell(  CSkillArea(*src,skillid,skilllv,tick,flag|BCT_ENEMY|1, skill_castend_damage_id), x,y, BL_ALL);
				x += dirx[dir];
				y += diry[dir];
			}
			skill_attack(BF_WEAPON,src,src,bl,skillid,skilllv,tick,0);
		}
		break;

	case ALL_RESURRECTION:		// ���U���N�V����
	case PR_TURNUNDEAD:			// �^?���A���f�b�h
		if (*bl != BL_PC && bl->is_undead() )
			skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		else
		{
			block_list::freeblock_unlock();
			return 1;
		}
		break;

	// ���@�n�X�L��
	case MG_SOULSTRIKE:			// �\�E���X�g���C�N
	case NPC_DARKSTRIKE:		// �Ń\�E���X�g���C�N
	case MG_COLDBOLT:			// �R�[���h�{���g
	case MG_FIREBOLT:			// �t�@�C�A�[�{���g
	case MG_LIGHTNINGBOLT:		// ���C�g�j���O�{���g
	case WZ_EARTHSPIKE:			// �A�[�X�X�p�C�N
	case AL_HEAL:				// �q�[��
	case AL_HOLYLIGHT:			// �z�[���[���C�g
	case WZ_JUPITEL:			// ���s�e���T���_�[
	case NPC_DARKTHUNDER:		// �Ń��s�e��
	case NPC_MAGICALATTACK:		// MOB:���@��?�U?
	case PR_ASPERSIO:			// �A�X�y���V�I
	case MG_FROSTDIVER:		// �t���X�g�_�C�o�[
		skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		break;

	case WZ_WATERBALL:			// �E�H?�^?�{?��
		skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,flag);
		if (skilllv>1) {
			int cnt,range;
			range = (skilllv>3) ? 2 : skilllv/2;
			if(sd)
				cnt = skill_count_water(*src,range);
			else
				cnt = skill_get_num(skillid,skilllv);
			if (cnt > 0)
				skill_addtimerskill(src,tick+150,bl->id,0,0,skillid,skilllv,cnt,flag);
		}
		break;

	case PR_BENEDICTIO:			// ��?�~��
		if (bl->get_race() == 1 || bl->get_race() == 6)
			skill_attack(BF_MAGIC, src, src, bl, skillid, skilllv, tick, flag);
		break;

	// ���@�n��?�U?�X�L��
	case MG_NAPALMBEAT:			// �i�p?���r?�g
	case MG_FIREBALL:			// �t�@�C��?�{?��
	case WZ_SIGHTRASHER:		// �T�C�g���b�V���[
		if (flag & 1) {
			// �ʂɃ_��?�W��?����
			if (bl->id != skill_area_temp[1]){
				if(skillid == MG_FIREBALL){	// �t�@�C��?�{?���Ȃ璆�S����̋������v�Z
					skill_area_temp[0] = bl->get_distance(skill_area_temp[2], skill_area_temp[3]);
				}
				skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,
					skill_area_temp[0]| 0x0500);
			}
		} else {
			int ar;
			skill_area_temp[0]=0;
			skill_area_temp[1]=bl->id;
			switch (skillid) {
				case MG_NAPALMBEAT:
					ar = 1;
					// �i�p�[���r�[�g�͕��U�_���[�W�Ȃ̂œG�̐��𐔂���
					maps[bl->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick,flag|BCT_ENEMY,skill_area_sub_count),
						bl->x, bl->y, ar, BL_ALL);
					break;
				case MG_FIREBALL:
					ar = 2;
					skill_area_temp[2]=bl->x;
					skill_area_temp[3]=bl->y;
					// �^�[�Q�b�g�ɍU����������(�X�L���G�t�F�N�g�\��)
					skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,
							skill_area_temp[0]);
					break;
				case WZ_SIGHTRASHER:
				default:
					ar = 3;
					bl = src;
					status_change_end(src,SC_SIGHT,-1);
					break;
			}
			if (skillid==WZ_SIGHTRASHER) {
				// �X�L���G�t�F�N�g�\��
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			} else {
				// �^�[�Q�b�g�ɍU����������(�X�L���G�t�F�N�g�\��)
				skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,
						skill_area_temp[0]);
			}
			// �^�[�Q�b�g�ȊO�͈͓̔��̓G�S�̂ɏ������s��
			maps[bl->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY|1, skill_castend_damage_id),
				bl->x, bl->y, ar, BL_ALL);
		}
		break;

	case HW_NAPALMVULCAN: // Fixed By SteelViruZ
		if (flag & 1) {
			if (bl->id != skill_area_temp[1])
				skill_attack(BF_MAGIC, src, src, bl, skillid, skilllv, tick, skill_area_temp[0]);
		} else {
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;

			maps[bl->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag|BCT_ENEMY,skill_area_sub_count),
				bl->x, bl->y, 1, BL_ALL);
			skill_attack(BF_MAGIC, src, src, bl, skillid, skilllv, tick, skill_area_temp[0]);

			maps[bl->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag|BCT_ENEMY|1,skill_castend_damage_id),
				bl->x, bl->y, 1, BL_ALL);
		}
		break;

	case WZ_FROSTNOVA:			// �t���X�g�m���@
		maps[src->m].foreachinarea( CSkillAttackArea(BF_MAGIC, *src, *src, skillid, skilllv, tick, flag, BCT_ENEMY),
			src->x, src->y, 5, BL_ALL);
		break;
	// ���̑�
	case HT_BLITZBEAT:			// �u���b�c�r?�g
		if (flag & 1) {
			// �ʂɃ_��?�W��?����
			if (bl->id != skill_area_temp[1])
				skill_attack(BF_MISC, src, src, bl, skillid, skilllv, tick, skill_area_temp[0]|(flag&0xf00000));
		} else {
			skill_area_temp[0] = 0;
			skill_area_temp[1] = bl->id;
			if (flag & 0xf00000)
			{
				maps[bl->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, BCT_ENEMY, skill_area_sub_count),
					bl->x, bl->y, 1, BL_ALL);
			}
			// �܂��^?�Q�b�g�ɍU?��������
			skill_attack(BF_MISC, src, src, bl, skillid, skilllv, tick, skill_area_temp[0]|(flag&0xf00000));
			// ���̌�^?�Q�b�g�ȊO�̔�??�̓G�S?��?�����s��
			maps[bl->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, BCT_ENEMY|1,skill_castend_damage_id),
				bl->x, bl->y, 1, BL_ALL);
		}
		break;

	case CR_GRANDCROSS:			// �O�����h�N���X
	case NPC_GRANDDARKNESS:		// �ŃO�����h�N���X
		// �X�L�����j�b�g�z�u
		skill_castend_pos2(src,bl->x,bl->y,skillid,skilllv,tick,0);
		src->set_delay(1000);
		break;

	case TF_THROWSTONE:			// �Γ���
	case NPC_SMOKING:			// �X��?�L���O
		skill_attack(BF_MISC,src,src,bl,skillid,skilllv,tick,0 );
		break;

	// Celest
	case PF_SOULBURN:
		if (rand()%100 < (skilllv < 5 ? 30 + skilllv * 10 : 70)) {
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if (skilllv == 5)
				skill_attack(BF_MAGIC,src,src,bl,skillid,skilllv,tick,0 );
			if (tsd && (maps[src->m].flag.pvp || maps[src->m].flag.gvg)) {
				tsd->status.sp = 0;
				clif_updatestatus(*tsd,SP_SP);
			}
		} else {
			clif_skill_nodamage(*src,*src,skillid,skilllv,1);
			if (skilllv == 5)
				skill_attack(BF_MAGIC,src,src,src,skillid,skilllv,tick,0 );
			if (sd) {
				sd->status.sp = 0;
				clif_updatestatus(*sd,SP_SP);
			}
		}		
		if (sd) pc_blockskill_start(*sd, skillid, (skilllv < 5 ? 10000: 15000));
		break;

	case NPC_SELFDESTRUCTION:	// ����
			if (flag & 1) {
				// �ʂɃ_���[�W��^����
				if (bl->id != skill_area_temp[1])
					skill_attack(BF_MISC, src, src, bl, NPC_SELFDESTRUCTION, skilllv, tick, flag);
			} else if(*bl==BL_PC){
				skill_area_temp[1] = bl->id;
				skill_area_temp[2] = 999999;
				clif_skill_nodamage(*src,*src, NPC_SELFDESTRUCTION, 0xFFFF, 1);

				maps[bl->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag|BCT_ENEMY|1,skill_castend_damage_id),
					bl->x, bl->y, 10, BL_ALL);
				battle_damage(src, src, skill_area_temp[2], 0);
			}
			else
			{
				skill_area_temp[1] = bl->id;
				skill_area_temp[2] = src->get_hp();
				clif_skill_nodamage(*src,*src, NPC_SELFDESTRUCTION, 0xFFFF, 1);

				maps[bl->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag|BCT_ENEMY|1,skill_castend_damage_id),
					bl->x, bl->y, 5, BL_ALL);
				battle_damage(src, src, skill_area_temp[2], 0);
			}
			break;

	// HP�z?/HP�z?���@
	case NPC_BLOODDRAIN:
	case NPC_ENERGYDRAIN:
		{
			int heal = skill_attack( (skillid == NPC_BLOODDRAIN) ? BF_WEAPON : BF_MAGIC,
					src, src, bl, skillid, skilllv, tick, flag);
			if (heal > 0)
			{
				block_list tbl;
				tbl.id = 0;
				tbl.m = src->m;
				tbl.x = src->x;
				tbl.y = src->y;
				clif_skill_nodamage(tbl, *src, AL_HEAL, heal, 1);
				battle_heal(NULL, src, heal, 0, 0);
			}
		}
		break;

	case 0:
		if(sd) {
			if (flag & 3){
				if (bl->id != skill_area_temp[1])
					skill_attack(BF_WEAPON, src, src, bl, skillid, skilllv, tick, 0x0500);
			} else {
				int ar = sd->splash_range;
				skill_area_temp[1] = bl->id;
				maps[bl->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag | BCT_ENEMY | 1,skill_castend_damage_id),
					bl->x, bl->y, ar, BL_ALL);
			}
		}
		break;

	default:
		ShowMessage("Unknown skill used (skill_castend_damage_id):%d\n",skillid);
		block_list::freeblock_unlock();
		return 1;
	}

	if( src->has_status(SC_MAGICPOWER) && skillid != HW_MAGICPOWER)
		status_change_end(src,SC_MAGICPOWER,-1);
	
	block_list::freeblock_unlock();	
	return 0;
}

/*==========================================
 * �X�L���g�p�i�r�������AID�w��x���n�j
 *------------------------------------------
 */
int skill_castend_nodamage_id( block_list *src, block_list *bl,unsigned short skillid,unsigned short skilllv,unsigned long tick,int flag )
{
	map_session_data *sd = NULL;
	map_session_data *dstsd = NULL;
	struct mob_data *md = NULL;
	struct mob_data *dstmd = NULL;
	int i;
	int sc_def_vit, sc_def_mdef;
//	int sc_dex, sc_luk;
	

	if(skillid > 0 && skilllv <= 0) return 0;	// celest

	nullpo_retr(1, src);
	nullpo_retr(1, bl);

	if (src->m != bl->m)
		return 1;

	(sd = src->get_sd()) && (md=src->get_md());
	if( sd && skill_not_ok(skillid, *sd) ) // [MouseJstr]
		return 0;

//	sc_dex = status_get_mdef (bl);
//	sc_luk = bl->get_luk ();
	sc_def_vit = status_get_sc_def_vit (bl);
	sc_def_mdef = status_get_sc_def_mdef (bl);

	(dstsd = bl->get_sd()) && (dstmd = bl->get_md());

	if( !bl->is_on_map() )
		return 1;
	if(sd && sd->is_dead())
		return 1;
	if(dstsd && dstsd->is_dead() && skillid != ALL_RESURRECTION)
		return 1;
	if( bl->get_class() == MOBID_EMPERIUM )
		return 1;

	block_list::freeblock_lock();
	switch(skillid)
	{
	case AL_HEAL:				// �q?��
		{
			int heal = skill_calc_heal(src, skilllv);
			int heal_get_jobexp;
			int skill;
			if (skilllv > 10)
				heal = 9999; //9999�q�[��
			if (status_isimmune(bl))
				heal=0;	// ?��峃J?�h�i�q?���ʂO�j
			if (sd) {
				if ((skill = sd->skill_check( HP_MEDITATIO)) > 0) // ���f�B�e�C�e�B�I
					heal += heal * skill * 2 / 100;
				if (sd && dstsd && sd->status.partner_id == dstsd->status.char_id &&
					pc_calc_base_job2(sd->status.class_) == 23 && sd->status.sex == 0) //������?�ۂ�PC�A?�ۂ������̃p?�g�i?�A�������X�p�m�r�A���������Ȃ�
					heal = heal*2;	//�X�p�m�r�̉ł��U�߂Ƀq?�������2�{�ɂȂ�
			}
			
			clif_skill_nodamage (*src, *bl, skillid, heal, 1);
			heal_get_jobexp = battle_heal(NULL,bl,heal,0,0);
			
			// JOB??�l�l��
			if(sd && dstsd && heal > 0 && sd != dstsd && config.heal_exp > 0){
				heal_get_jobexp = heal_get_jobexp * config.heal_exp / 100;
				if (heal_get_jobexp <= 0)
					heal_get_jobexp = 1;
				pc_gainexp (*sd, 0, heal_get_jobexp);
			}
		}
		break;

	case ALL_RESURRECTION:
		if(dstsd) {
			int per = 0;
			if (maps[bl->m].flag.pvp && dstsd->pvp_point == 0)
				break;

			if( dstsd->is_dead() )
			{	// ���S���� 
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
				switch(skilllv){
				case 1: per=10; break;
				case 2: per=30; break;
				case 3: per=50; break;
				case 4: per=80; break;
				}
				dstsd->status.hp = dstsd->status.max_hp * per / 100;
				if (dstsd->status.hp <= 0) dstsd->status.hp = 1;
				if(dstsd->state.restart_full_recover) {	// �I�V���X�J?�h
					dstsd->status.hp = dstsd->status.max_hp;
					dstsd->status.sp = dstsd->status.max_sp;
				}
				dstsd->set_stand();
				if(config.pc_invincible_time > 0)
					pc_setinvincibletimer(*dstsd, config.pc_invincible_time);
				clif_updatestatus(*dstsd, SP_HP);
				clif_resurrection(*bl, 1);
				if(sd && sd != dstsd && config.resurrection_exp > 0) {
					int exp = 0,jexp = 0;
					int lv = dstsd->status.base_level - sd->status.base_level, jlv = dstsd->status.job_level - sd->status.job_level;
					if(lv > 0) {
						exp = dstsd->status.base_exp * lv * config.resurrection_exp / 1000000;
						if (exp < 1) exp = 1;
					}
					if(jlv > 0) {
						jexp = dstsd->status.job_exp * lv * config.resurrection_exp / 1000000;
						if (jexp < 1) jexp = 1;
					}
					if(exp > 0 || jexp > 0)
						pc_gainexp (*sd, exp, jexp);
				}
			}
		}
		break;

	case AL_DECAGI:			// ���x����
		if (status_isimmune(bl))
			break;

		if (rand() % 100 < (40 + skilllv * 2 + (src->get_lv() + bl->get_int())/5 +(sc_def_mdef-100)))
		{	//0 defense is sc_def_mdef == 100! [Skotlex]
			int time = skill_get_time(skillid,skilllv);
			if (*bl == BL_PC) time/=2; //Halved duration for Players
			clif_skill_nodamage (*src, *bl, skillid, skilllv, 1);
			status_change_start (bl, (status_t)SkillStatusChangeTable[skillid], skilllv, 0, 0, 0, time, 0);
		}
		break;

	case AL_CRUCIS:
		if (flag & 1) {
			int race = bl->get_race();
			if( battle_check_target (src, bl, BCT_ENEMY) && (race == 6 || bl->is_undead()) )
			{
				int slv = src->get_lv(),tlv = bl->get_lv();
				int rate = 23 + skilllv*4 + slv - tlv;
				if (rand()%100 < rate)
					status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,0,0);
			}
		} else {
			clif_skill_nodamage(*src, *bl, skillid, skilllv, 1);
			maps[src->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag|BCT_ENEMY|1,skill_castend_nodamage_id),
				src->x, src->y, 15, BL_ALL);
		}
		break;

	case PR_LEXDIVINA:		// ���b�N�X�f�B�r?�i
		{
			clif_skill_nodamage (*src, *bl, skillid, skilllv, 1);
			if (status_isimmune(bl))
				break;
			if( bl->has_status(SC_DIVINA) )
				status_change_end(bl,SC_DIVINA, -1);
			else if (rand() % 100 < sc_def_vit) {
				status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}
		}
		break;

	case SA_ABRACADABRA:
		{
			int abra_skillid = 0, abra_skilllv;
			if (sd)
			{ //Crash-fix [Skotlex]
				//require 1 yellow gemstone even with mistress card or Into the Abyss
				if((i = pc_search_inventory(*sd, 715)) < 0 )
				{ //bug fixed by Lupus (item pos can be 0, too!)
					sd->skill_failed(sd->skillid);
					break;
				}
				pc_delitem(*sd, i, 1, 0);
			}
			do {
				abra_skillid = rand() % 331;
				if (skill_abra_db[abra_skillid].req_lv > skilllv ||
					rand()%10000 >= skill_abra_db[abra_skillid].per ||		//db�Ɋ�Â����x��?�m������
					(abra_skillid >= NPC_PIERCINGATT && abra_skillid <= NPC_SUMMONMONSTER) ||	//NPC�X�L���̓_��
					skill_get_unit_flag(abra_skillid) & UF_DANCE)	//���t�X�L���̓_��
						abra_skillid = 0;	// reset to get a new id
			} while (abra_skillid == 0);
			abra_skilllv = skill_get_max(abra_skillid) >  skilllv ? skilllv : skill_get_max(abra_skillid);
			clif_skill_nodamage (*src, *bl, skillid, skilllv, 1);
			if (sd)
			{	//Crash-protection against Abracadabra casting pets
				sd->skillitem = abra_skillid;
				sd->skillitemlv = abra_skilllv;
				sd->state.abra_flag = 1;
				clif_item_skill (*sd, abra_skillid, abra_skilllv, "Abracadabra");
			}
			else if(*src == BL_PET)
			{	// [Skotlex]
				struct pet_data *pd = (struct pet_data *)src;
				int inf = skill_get_inf(abra_skillid);
				if (inf & (INF_SELF_SKILL|INF_SUPPORT_SKILL))//Self-Skills, Supportive skills
					pet_skill_use(*pd, pd->msd, abra_skillid, abra_skilllv, tick); 
				else //Assume offensive skills
					pet_skill_use(*pd, *bl, abra_skillid, abra_skilllv, tick); 
			}
		}
		break;

	case SA_COMA:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if (status_isimmune(bl))
			break;
		if (dstsd) {			
			dstsd->status.hp = 1;
			dstsd->status.sp = 1;
			clif_updatestatus(*dstsd, SP_HP);
			clif_updatestatus(*dstsd, SP_SP);
		}
		if(dstmd) dstmd->hp = 1;
		break;
	case SA_FULLRECOVERY:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if (status_isimmune(bl))
			break;
		if (dstsd) dstsd->heal (dstsd->status.max_hp, dstsd->status.max_sp);
		else if (dstmd) dstmd->hp = bl->get_max_hp();
		break;
	case SA_SUMMONMONSTER:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(sd) mob_once_spawn(sd,maps[src->m].mapname,src->x,src->y,"--ja--",-1,1,"");
		break;
	case SA_LEVELUP:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if (sd && pc_nextbaseexp(*sd)) pc_gainexp(*sd, pc_nextbaseexp(*sd) * 10 / 100, 0);
		break;
	case SA_INSTANTDEATH:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if (sd) pc_damage(*sd,sd->status.max_hp, NULL);
		break;
	case SA_QUESTION:
	case SA_GRAVITY:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		break;
	case SA_CLASSCHANGE:
		{
			//�N���X�`�F���W�p�{�X�����X�^?ID
			static int changeclass[]={1038,1039,1046,1059,1086,1087,1112,1115
				,1157,1159,1190,1272,1312,1373,1492};
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if(dstmd) mob_class_change(*dstmd,changeclass, sizeof(changeclass)/sizeof(changeclass[0]));
		}
		break;
	case SA_MONOCELL:
		{
			static int poringclass[]={1002};
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if(dstmd) mob_class_change(*dstmd,poringclass,1);
		}
		break;
	case SA_DEATH:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if (dstsd) pc_damage(*dstsd,dstsd->status.max_hp,NULL);
		if (dstmd) mob_damage(*dstmd,dstmd->hp,1,NULL);
		break;
	case SA_REVERSEORCISH:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if (dstsd) pc_setoption(*dstsd,dstsd->status.option|0x0800);
		break;
	case SA_FORTUNE:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(sd) pc_getzeny(*sd,bl->get_lv()*100);
		break;
	case SA_TAMINGMONSTER:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if (dstmd && sd) {
			for (i = 0; i < MAX_PET_DB; ++i) {
				if (dstmd->class_ == pet_db[i].class_) {
					pet_catch_process1(*sd, dstmd->class_);
					break;
				}
			}
		}
		break;

	case AL_INCAGI:			// ���x?��
	case AL_BLESSING:		// �u���b�V���O
	case PR_SLOWPOISON:
	case PR_IMPOSITIO:		// �C���|�V�e�B�I�}�k�X
	case PR_LEXAETERNA:		// ���b�N�X�G?�e���i
	case PR_SUFFRAGIUM:		// �T�t���M�E��
	case PR_BENEDICTIO:		// ��?�~��
	case CR_PROVIDENCE:		// �v�����B�f���X
		if (status_isimmune(bl))
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		else {
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;

	case CG_MARIONETTE:		// �}���I�l�b�g�R���g��?��
	{
		status_t sc1 = (status_t)SkillStatusChangeTable[skillid];
		status_t sc2 = SC_MARIONETTE2;

		if( sd && ((sd == dstsd) || (!sd->status.party_id) || 
			(sd->status.party_id != dstsd->status.party_id)) )
		{
			sd->skill_failed(skillid);
			block_list::freeblock_unlock();
			return 1;
		}
		if( !src->has_status(sc1) && !bl->has_status(sc2) )
		{
			status_change_start (src,sc1,skilllv,0,bl->id,0,skill_get_time(skillid,skilllv),0);
			status_change_start (bl,sc2,skilllv,0,src->id,0,skill_get_time(skillid,skilllv),0);
			clif_marionette(*src, bl);
		}
		else if( src->has_status(sc1) && bl->has_status(sc2) &&
			(uint32)src->get_statusvalue3(sc1).integer() == bl->id && 
			(uint32)bl->get_statusvalue3(sc2).integer() == src->id)
		{
			status_change_end(src, sc1, -1);
			status_change_end(bl, sc2, -1);
			clif_marionette(*src, NULL);
		}
		else
		{
			sd->skill_failed(skillid);
			block_list::freeblock_unlock();
			return 1;
		}
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		break;
	}
	case SA_FLAMELAUNCHER:	// added failure chance and chance to break weapon if turned on [Valaris]
	case SA_FROSTWEAPON:
	case SA_LIGHTNINGLOADER:
	case SA_SEISMICWEAPON:
		if (dstsd) {
			if (status_isimmune(bl)) {
				clif_skill_nodamage(*src,*bl,skillid,skilllv,0);
				break;
			}
			if(dstsd->status.weapon == 0 ||
				(sd && sd->status.party_id > 0 && sd->status.party_id != dstsd->status.party_id) ||
				dstsd->has_status(SC_FLAMELAUNCHER) ||
				dstsd->has_status(SC_FROSTWEAPON) ||
				dstsd->has_status(SC_LIGHTNINGLOADER) ||
				dstsd->has_status(SC_SEISMICWEAPON) ||
				dstsd->has_status(SC_ENCPOISON) )
			{
				if (sd) sd->skill_failed(skillid);
				clif_skill_nodamage(*src,*bl,skillid,skilllv,0);
				break;
			}
		}
		if (sd)
		{
			i = pc_search_inventory (*sd, skill_db[skillid].itemid[0]);
			if(i < 0 || sd->status.inventory[i].amount < skill_db[skillid].amount[0])
			{
				sd->skill_failed(skillid);
				break;
			}
			pc_delitem(*sd, i, skill_db[skillid].amount[0], 0);
		}

		if(skilllv < 4 && rand()%100 > (60+skilllv*10) ) { // 100% success rate at lv4 & 5, but lasts longer at lv5
			if (sd) sd->skill_failed(skillid);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,0);
			if(dstsd && config.equip_self_break_rate) {
				if(sd && sd != dstsd) clif_displaymessage(sd->fd,"You broke target's weapon");
				pc_breakweapon(*dstsd);
			}
			break;
		} else {
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;

	case PR_ASPERSIO:		// �A�X�y���V�I
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if (status_isimmune(bl) || dstmd)
			break;
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;

	case PR_KYRIE:			// �L���G�G���C�\��
		clif_skill_nodamage(*bl,*bl,skillid,skilllv,1);
		if (status_isimmune(bl))
			break;
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;

	case LK_BERSERK:		// �o?�T?�N
		if(config.berserk_cancels_buffs)
		{
			status_change_end(bl,SC_TWOHANDQUICKEN,-1);
			status_change_end(bl,SC_CONCENTRATION,-1);
			status_change_end(bl,SC_PARRYING,-1);
			status_change_end(bl,SC_ENDURE,-1);
			status_change_end(bl,SC_AURABLADE,-1);
		}
	case KN_AUTOCOUNTER:		// �I?�g�J�E���^?
	case KN_TWOHANDQUICKEN:	// �c?�n���h�N�C�b�P��
	case CR_SPEARQUICKEN:	// �X�s�A�N�C�b�P��
	case CR_REFLECTSHIELD:
	case AS_POISONREACT:	// �|�C�Y�����A�N�g
	case MC_LOUD:			// ���E�h�{�C�X
	case MG_ENERGYCOAT:		// �G�i�W?�R?�g
	case MG_SIGHT:			// �T�C�g
	case AL_RUWACH:			// ���A�t
	case MO_EXPLOSIONSPIRITS:	// �����g��
	case MO_STEELBODY:		// ����
	case LK_AURABLADE:		// �I?���u��?�h
	case LK_PARRYING:		// �p���C���O
	case LK_CONCENTRATION:	// �R���Z���g��?�V����
	case WS_CARTBOOST:		// �J?�g�u?�X�g
	case SN_SIGHT:			// �g�D��?�T�C�g
	case WS_MELTDOWN:		// �����g�_�E��
	case WS_OVERTHRUSTMAX:	// Overthrust Max [Celest]
	case ST_REJECTSWORD:	// ���W�F�N�g�\?�h
	case HW_MAGICPOWER:		// ���@��?��
	case PF_MEMORIZE:		// �������C�Y
	case PA_SACRIFICE:
	case ASC_EDP:			// [Celest]
	case CG_MOONLIT:		// ������̐�ɗ�����Ԃт�
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;
	case HP_ASSUMPTIO:		// 
		if (flag&1)
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		else
		{
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			maps[bl->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag|BCT_ALL|1,skill_castend_nodamage_id),
				bl->x, bl->y, 1, BL_PC);
		}
		break;
	case SM_ENDURE:			// �C���f���A
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		if(sd) pc_blockskill_start(*sd, skillid, 10000);
		break;

	case SM_AUTOBERSERK:	// Celest
		{
			status_t sc = (status_t)SkillStatusChangeTable[skillid];
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if( bl->has_status(sc) )
				status_change_end(bl, sc, -1);
			else
				status_change_start(bl,sc,skilllv,0,0,0,0,0);
		}
		break;

	case AS_ENCHANTPOISON: // Prevent spamming [Valaris]
		if (dstsd) {
			if( dstsd->has_status(SC_FLAMELAUNCHER) || dstsd->has_status(SC_FROSTWEAPON) ||
				dstsd->has_status(SC_LIGHTNINGLOADER) || dstsd->has_status(SC_SEISMICWEAPON) ||
				dstsd->has_status(SC_ENCPOISON) )
			{
				clif_skill_nodamage(*src,*bl,skillid,skilllv,0);
				sd->skill_failed(skillid);
				break;
			}
		}
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;

	case LK_TENSIONRELAX:	// �e���V���������b�N�X
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		sd->set_sit();
		clif_sitting(*sd);
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;

	case MC_CHANGECART:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		break;

	case AC_CONCENTRATION:	// �W���͌���
		{
			const int range = 1;
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
			maps[src->m].foreachinarea( CStatusChangetimer(*src,SkillStatusChangeTable[skillid],tick),
				src->x, src->y, range, BL_ALL);
		}
		break;

	case SM_PROVOKE:		// �v���{�b�N
		{
			// MVPmob�ƕs���ɂ�?���Ȃ� 
			if((dstmd && bl->get_mode()&0x20) || bl->is_undead() )
			{	//�s���ɂ�?���Ȃ�
				block_list::freeblock_unlock();
				return 1;
			}

			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if(rand()%100 > (50 + 3*skilllv + src->get_lv() - bl->get_lv())) //TODO: How much does base level affects? Dummy value of 1% per level difference used. [Skotlex]
			{
				if (sd) 
					sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );

			if(dstmd && dstmd->skilltimer!=-1 && dstmd->state.skillcastcancel)	// �r���W�Q
				skill_castcancel(bl,0);
			if(dstsd && dstsd->skilltimer!=-1 && (!dstsd->state.no_castcancel || maps[bl->m].flag.gvg)
				&& dstsd->state.skillcastcancel	&& !dstsd->state.no_castcancel2)
				skill_castcancel(bl,0);

			if(bl->has_status(SC_FREEZE))
				status_change_end(bl,SC_FREEZE,-1);
			if(bl->has_status(SC_STONE) && bl->get_statusvalue2(SC_STONE).integer()==0)
				status_change_end(bl,SC_STONE,-1);
			if(bl->has_status(SC_SLEEP))
				status_change_end(bl,SC_SLEEP,-1);

			if(dstmd) {
				int range = skill_get_range(skillid,skilllv);
				dstmd->provoke_id = src->id;
				mob_target(*dstmd,src,range);
			}
		}
		break;

	case CR_DEVOTION:		// �f�B�{?�V����
		if(sd && dstsd){
			//?����{�q�̏ꍇ�̌��̐E�Ƃ��Z�o����
			int s_class = pc_calc_base_job2 (dstsd->status.class_);

			unsigned int lv = abs(sd->status.base_level - dstsd->status.base_level);
			if ((sd == dstsd)									// �����PC����Ȃ��Ƃ���
			 || (sd->block_list::id == dstsd->block_list::id)						// ���肪�����͂���
			 || (lv > config.devotion_level_difference)	// ���x�����}10�܂�
			 || (!sd->status.party_id && !sd->status.guild_id)	// PT�ɂ��M���h�ɂ���?�����͂���
			 || ((sd->status.party_id != dstsd->status.party_id)	// �����p?�e�B?���A
				&&(sd->status.guild_id != dstsd->status.guild_id))	// �����M���h����Ȃ��Ƃ���
			 || (s_class == 14 || s_class == 21)) {	// �N���Z����
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 1;
			}
			for (i = 0; i < skilllv; ++i) {
				if (!sd->dev.val1[i]) {		// �󂫂�������������
					sd->dev.val1[i] = bl->id;
					sd->dev.val2[i] = bl->id;
					break;
				} else if (i == skilllv - 1) {		// �󂫂��Ȃ�����
					sd->skill_failed(skillid);
					block_list::freeblock_unlock();
					return 1;
				}
			}
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			clif_devotion(*sd,bl->id);
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],src->id,1,0,0,1000*(15+15*skilllv),0 );
		}
		else sd->skill_failed(skillid);
		break;

	case MO_CALLSPIRITS:	// ?��
		if(sd) {
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			pc_addspiritball(*sd,skill_get_time(skillid,skilllv),skilllv);
		}
		break;

	case CH_SOULCOLLECT:	// ��?��
		if(sd) {
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			for (i = 0; i < 5; ++i)
				pc_addspiritball(*sd,skill_get_time(skillid,skilllv),5);
		}
		break;

	case MO_BLADESTOP:	// ���n���
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		status_change_start(src,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;

	case MO_ABSORBSPIRITS:	// ?�D
		i = 0;
		if (dstsd && dstsd->spiritball > 0 &&
			((sd && sd == dstsd) || maps[src->m].flag.pvp || maps[src->m].flag.gvg))
		{
			i = dstsd->spiritball * 7;
			pc_delspiritball(*dstsd,dstsd->spiritball,0);
		} else if (dstmd && //?�ۂ������X�^?�̏ꍇ
			//20%�̊m����?�ۂ�Lv*2��SP���񕜂���B���������Ƃ��̓^?�Q�b�g(��?�D?)��????!!
			!(mob_db[dstmd->class_].mode & 0x20) && rand() % 100 < 20)
		{
			i = 2 * mob_db[dstmd->class_].lv;
			mob_target(*dstmd,src,0);
		}
		if (sd){
			if (i > 0x7FFF)
				i = 0x7FFF;
			if (sd->status.sp + i > sd->status.max_sp)
				i = sd->status.max_sp - sd->status.sp;
			if (i) {
				sd->status.sp += i;
				clif_heal(sd->fd,SP_SP,i);
			}
		}
		clif_skill_nodamage(*src,*bl,skillid,skilllv,0);
		break;

	case AC_MAKINGARROW:			// ��쐬
		if(sd) {
			clif_arrow_create_list(*sd);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;

	case AM_PHARMACY:			// �|?�V�����쐬
		if(sd) {
			clif_skill_produce_mix_list(*sd,32);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;


	case AM_TWILIGHT1:
		if(sd)
		{
			//skill_am_twilight1(sd);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;
	case AM_TWILIGHT2:
		if(sd)
		{
			//skill_am_twilight2(sd);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;
	case AM_TWILIGHT3:
		if(sd)
		{
			//skill_am_twilight3(sd);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;
	case AM_CALLHOMUN:	// �R�[���z�����N���X
		if(sd && homun_data::call_homunculus(*sd) )
		{
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;
	case AM_REST:				// ����
		if( sd && sd->hd && sd->hd->return_to_embryo() )
		{
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;
	case AM_RESURRECTHOMUN:				// ���U���N�V�����z�����N���X
		if( sd && sd->hd )
		{
			if( sd->hd->revive(skilllv) )
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			else
				sd->skill_failed(AM_RESURRECTHOMUN);
		}
		break;

	case WS_CREATECOIN:				// �N���G�C�g�R�C��
		if(sd) {
			clif_skill_produce_mix_list(*sd,64);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;
	case WS_CREATENUGGET:			// �򐻑�
		if(sd) {
			clif_skill_produce_mix_list(*sd,128);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;
	case ASC_CDP: // [DracoRPG]
		// notes: success rate (from emperium.org) = 20 + [(20*Dex)/50] + [(20*Luk)/100]
		if(sd) {
			clif_skill_produce_mix_list(*sd,256);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;

	case BS_HAMMERFALL:		// �n���}?�t�H?��
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(dstsd && dstsd->state.no_weapon_damage)
			break;
		if(rand() % 100 < (20 + 10 * skilllv) * sc_def_vit / 100 )
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case RG_RAID:			// �T�v���C�Y�A�^�b�N
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		maps[bl->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY|1,skill_castend_damage_id),
			bl->x, bl->y, 1, BL_ALL);
		status_change_end(src, SC_HIDING, -1);	// �n�C�f�B���O����
		break;

	case ASC_METEORASSAULT:	// ���e�I�A�T���g
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);

		maps[bl->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY|1,skill_castend_damage_id),
			bl->x, bl->y, 2, BL_ALL);
		break;

	case KN_BRANDISHSPEAR:	// �u�����f�B�b�V���X�s�A
		{
			int c,n=4;
			//int ar=skilllv/3;
			dir_t dir = src->get_direction(*bl);
			struct square tc;
			int x=bl->x,y=bl->y;
			
			skill_brandishspear_first(&tc,dir,x,y);
			skill_brandishspear_dir(&tc,dir,4);
			// ��?�C
			if(skilllv == 10)
			{
				for(c=1;c<4;++c)
				{
					maps[bl->m].foreachincell(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY|n,skill_castend_damage_id),
						tc.val1[c],tc.val2[c],BL_ALL);
				}
			}
			// ��?�B�A
			if(skilllv > 6){
				skill_brandishspear_dir(&tc,dir,-1);
				n--;
			}else{
				skill_brandishspear_dir(&tc,dir,-2);
				n-=2;
			}

			if(skilllv > 3){
				for(c=0;c<5;++c)
				{
					maps[bl->m].foreachincell(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY|n,skill_castend_damage_id),
						tc.val1[c],tc.val2[c],BL_ALL);
					if(skilllv > 6 && n==3 && c==4){
						skill_brandishspear_dir(&tc,dir,-1);
						n--;c=-1;
					}
				}
			}
			// ��?�@
			for(c=0;c<10;++c)
			{
				if(c==0||c==5) skill_brandishspear_dir(&tc,dir,-1);
				maps[bl->m].foreachincell(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ENEMY|1,skill_castend_damage_id),
					tc.val1[c%5],tc.val2[c%5],BL_ALL);
			}
		}
		break;

	// �p?�e�B�X�L��
	case AL_ANGELUS:		// �G���W�F���X
	case PR_MAGNIFICAT:		// �}�O�j�t�B�J?�g
	case PR_GLORIA:			// �O�����A
	case SN_WINDWALK:		// �E�C���h�E�H?�N
		if (sd == NULL || sd->status.party_id == 0 || (flag & 1)) {
			// �ʂ�?��
			clif_skill_nodamage(*bl,*bl,skillid,skilllv,1);
			if(status_isimmune(bl))
				break;
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		} else if (sd) {
			// �p?�e�B�S?�ւ�?��

			block_list::foreachpartymemberonmap(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_PARTY|1,skill_castend_nodamage_id), *sd,true);
		}
		break;

	case BS_ADRENALINE:		// �A�h���i�������b�V��
	case BS_WEAPONPERFECT:	// �E�F�|���p?�t�F�N�V����
	case BS_OVERTHRUST:		// �I?�o?�g���X�g
		if (sd == NULL || sd->status.party_id == 0 || (flag & 1))
		{	// �ʂ�?�� 
			clif_skill_nodamage(*bl,*bl,skillid,skilllv,1);
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,(src == bl)? 1:0,0,0,skill_get_time(skillid,skilllv),0);
		}
		else if (sd)
		{	// �p?�e�B�S?�ւ�?�� 
			block_list::foreachpartymemberonmap(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_PARTY|1,skill_castend_nodamage_id), *sd,true);
		}
		break;

	// �i�t���Ɖ������K�v�j 
	case BS_MAXIMIZE:		// �}�L�V�}�C�Y�p��?
	case NV_TRICKDEAD:		// ���񂾂ӂ�
	case CR_DEFENDER:		// �f�B�t�F���_?
	case CR_AUTOGUARD:		// �I?�g�K?�h
		{
			status_t sc = (status_t)SkillStatusChangeTable[skillid];
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if( bl->has_status(sc) )
				status_change_end(bl, sc, -1);
			else
				status_change_start(bl,sc,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);				
		}
		break;
	
	case TK_READYSTORM:
	case TK_READYDOWN:
	case TK_READYTURN:
	case TK_READYCOUNTER:
	case TK_DODGE:
		{
			if( (bl->has_status(SC_READYSTORM) && skillid != TK_READYSTORM) ||
				(bl->has_status(SC_READYDOWN) && skillid != TK_READYDOWN) ||
				(bl->has_status(SC_READYTURN) && skillid != TK_READYTURN) ||
				(bl->has_status(SC_READYCOUNTER) && skillid != TK_READYCOUNTER) ||
				(bl->has_status(SC_DODGE) && skillid != TK_DODGE) )
				sd->skill_failed(skillid);
			else
			{
				status_t sc = (status_t)SkillStatusChangeTable[skillid];
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
				if( bl->has_status(sc) )
					status_change_end(bl, sc, -1);
				else
					status_change_start(bl,sc,skilllv,0,0,0,0,0);
			}
		}
		break;
	case TK_RUN:
	case TF_HIDING:			// �n�C�f�B���O
	case ST_CHASEWALK:			// �n�C�f�B���O
		{
			status_t sc = (status_t)SkillStatusChangeTable[skillid];
			//clif_skill_nodamage(*src,*bl,skillid,0xFFFF,1);
			if( bl->has_status(sc) )
				// ��������
				status_change_end(bl, sc, -1);
			else
				// �t������
				status_change_start(bl,sc,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case AS_CLOAKING:		// �N��?�L���O
		{
			status_t sc = (status_t)SkillStatusChangeTable[skillid];
			//clif_skill_nodamage(*src,*bl,skillid,0xFFFF,1);
			if( bl->has_status(sc) )
				// ��������
				status_change_end(bl, sc, -1);
			else
			{	// �t������
				//Avoid cloaking with no wall and low skill level. [Skotlex]
				if (sd && skilllv < 3 && skill_check_cloaking(bl))
					sd->skill_failed(skillid);
				else
					status_change_start(bl,sc,skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
			}

		}
		break;

	// ?�n�X�L��
	case BD_LULLABY:			// �q��S
	case BD_RICHMANKIM:			// �j�����h�̉�
	case BD_ETERNALCHAOS:		// �i���̍���
	case BD_DRUMBATTLEFIELD:	// ?���ۂ̋���
	case BD_RINGNIBELUNGEN:		// �j?�x�����O�̎w��
	case BD_ROKISWEIL:			// ���L�̋���
	case BD_INTOABYSS:			// �[���̒���
	case BD_SIEGFRIED:			// �s���g�̃W?�N�t��?�h
	case BA_DISSONANCE:			// �s���a��
	case BA_POEMBRAGI:			// �u���M�̎�
	case BA_WHISTLE:			// ���J
	case BA_ASSASSINCROSS:		// �[�z�̃A�T�V���N���X
	case BA_APPLEIDUN:			// �C�h�D���̗ь�
	case DC_UGLYDANCE:			// ��������ȃ_���X
	case DC_HUMMING:			// �n�~���O
	case DC_DONTFORGETME:		// ����Y��Ȃ��Łc
	case DC_FORTUNEKISS:		// �K�^�̃L�X
	case DC_SERVICEFORYOU:		// �T?�r�X�t�H?��?
	case CG_HERMODE:			// Wand of Hermod
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		break;

	case HP_BASILICA:			// �o�W���J
		{
			struct skill_unit_group *sg;
			src->stop_walking(1);
			skill_clear_unitgroup(src);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			sg = skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
			status_change_start(src,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,basics::numptr(sg),
				skill_get_time(skillid,skilllv),0);
		}
		break;

	case PA_GOSPEL:				// �S�X�y��
		skill_clear_unitgroup(src);
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		skill_unitsetting(src,skillid,skilllv,src->x,src->y,0);
		status_change_start(src,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,BCT_SELF,skill_get_time(skillid,skilllv),0);
		break;

	case BD_ADAPTATION:			// �A�h���u
		{
			if( src->has_status(SC_DANCING) )
			{
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
				skill_stop_dancing(src,0);
			}
		}
		break;

	case BA_FROSTJOKE:			// �����W��?�N
	case DC_SCREAM:				// �X�N��?��
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		skill_addtimerskill(src,tick+3000,bl->id,0,0,skillid,skilllv,0,flag);
		if(md) {	// Mob�͒���Ȃ�����A�X�L���������΂��Ă݂�
			char temp[128];
			size_t sz=snprintf(temp,sizeof(temp), "%s: %s!!",md->name,skill_db[skillid].desc);
			clif_GlobalMessage(*md,temp,sz);
		}
		break;

	case TF_STEAL:			// �X�e�B?��
		if(sd) {
			if(pc_steal_item(*sd,bl))
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			else
				sd->skill_failed(skillid,SF_FAILED);
		}
		break;

	case RG_STEALCOIN:		// �X�e�B?���R�C��
		if(sd)
		{
			if(pc_steal_coin(*sd,bl)) {
				int range = skill_get_range(skillid,skilllv);
				if(range < 0)
					range = src->get_range() - (range + 1);
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
				mob_target(*((struct mob_data *)bl),src,range);
			}
			else
				sd->skill_failed(skillid);
		}
		break;

	case MG_STONECURSE:			// �X�g?���J?�X
		{
			// Level 6-10 doesn't consume a red gem if it fails [celest]
			int gem_flag = 1, fail_flag = 0;
			if (dstmd && bl->get_mode()&0x20) {
				if(sd) sd->skill_failed(sd->skillid);
				break;
			}
			
			if(status_isimmune(bl))
				break;
			if( bl->has_status(SC_STONE) )
			{
				status_change_end(bl,SC_STONE,-1);
				if (sd) {
					fail_flag = 1;
					sd->skill_failed(skillid);
				}
			}
			else if( rand()%100< skilllv*4+20 && !bl->is_undead())
			{
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
				status_change_start(bl,SC_STONE,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			}
			else if(sd) {
				if (skilllv > 5) gem_flag = 0;
				sd->skill_failed(skillid);
				fail_flag = 1;
			}
			if (dstmd)
				mob_target(*dstmd,src,skill_get_range(skillid,skilllv));
			if (sd && gem_flag) {
				if ((i=pc_search_inventory(*sd, skill_db[skillid].itemid[0])) < 0 ) {
					if (!fail_flag) sd->skill_failed(sd->skillid);
					break;
				}
				pc_delitem(*sd, i, skill_db[skillid].amount[0], 0);
			}
		}
		break;

	case NV_FIRSTAID:			// ?�}��?
		clif_skill_nodamage(*src,*bl,skillid,5,1);
		battle_heal(NULL,bl,5,0,0);
		break;

	case AL_CURE:				// �L���A?
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(status_isimmune(bl))
			break;
		status_change_end(bl, SC_SILENCE	, -1 );
		status_change_end(bl, SC_BLIND	, -1 );
		status_change_end(bl, SC_CONFUSION, -1 );
		if( bl->is_undead() )
		{	//�A���f�b�h�Ȃ�È�?��
			status_change_start(bl, SC_CONFUSION,1,0,0,0,6000,0);
		}
		break;

	case TF_DETOXIFY:			// ���
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		status_change_end(bl, SC_POISON	, -1 );
		status_change_end(bl, SC_DPOISON	, -1 );
		break;

	case PR_STRECOVERY:			// ���J�o��?
		{
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if(status_isimmune(bl))
				break;
			status_change_end(bl, SC_FREEZE	, -1 );
			status_change_end(bl, SC_STONE	, -1 );
			status_change_end(bl, SC_SLEEP	, -1 );
			status_change_end(bl, SC_STUN	, -1 );
			if( bl->is_undead() )
			{	//�A���f�b�h�Ȃ�È�?��
				if(rand()%100 < (100-(bl->get_int()/2+bl->get_vit()/3+bl->get_luk()/10)))
				{
					status_change_start(bl, SC_BLIND,1,0,0,0,
						1000 * 30 * (100-(bl->get_int()+bl->get_vit())/2)/100,0);
				}
			}
			if(dstmd){
				dstmd->attacked_id=0;
				dstmd->target_id=0;
				dstmd->state.targettype = NONE_ATTACKABLE;
				dstmd->state.skillstate=MSS_IDLE;
				dstmd->next_walktime=tick+rand()%3000+3000;
			}
		}
		break;

	case WZ_ESTIMATION:			// �����X�^?���
		if(sd && dstmd)
		{
			clif_skill_nodamage(*sd,*dstmd,skillid,skilllv,1);
			clif_skill_estimation(*sd,*dstmd);
		}
		break;

	case MC_IDENTIFY:			// �A�C�e���Ӓ�
		if(sd)
			clif_item_identify_list(*sd);
		break;

	case BS_REPAIRWEAPON:			// ����C��
		if(sd) {
//���삵�Ȃ��̂łƂ肠�����R�����g�A�E�g
			clif_item_repair_list(*sd);
		}
		break;

	// Weapon Refining [Celest]
	case WS_WEAPONREFINE:
		if(sd)
			clif_item_refine_list(*sd);
		break;

	case MC_VENDING:			// �I�X�J��
		if(sd)
			clif_openvendingreq(*sd,2+sd->skilllv);
		break;

	case AL_TELEPORT:			// �e���|?�g
		if(sd) {
			if (maps[sd->block_list::m].flag.noteleport) {	// �e���|�֎~
				clif_skill_teleportmessage(*sd,0);
				break;
			}
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if(sd->skilllv == 1)
				clif_skill_warppoint(*sd,sd->skillid,"Random","","","");
			else {
				clif_skill_warppoint(*sd,sd->skillid,"Random",
					sd->status.save_point.mapname,"","");
			}
		} else if(dstmd)
			mob_warp(*dstmd,-1,-1,-1,3);
		break;

	case AL_HOLYWATER:			// �A�N�A�x�l�f�B�N�^
		if(sd) {
			int eflag;
			struct item item_tmp(523);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if(config.holywater_name_input)
			{
				item_tmp.card[0] = 0xfe;
				item_tmp.card[1] = 0;
				item_tmp.card[2] = basics::GetWord(sd->status.char_id,0);	// �L����ID
				item_tmp.card[3] = basics::GetWord(sd->status.char_id,1);
			}
			eflag = pc_additem(*sd,item_tmp,1);
			if(eflag)
			{
				clif_additem(*sd,0,0,eflag);
				flooritem_data::create(item_tmp,1,sd->block_list::m,sd->block_list::x,sd->block_list::y,NULL,NULL,NULL,0);
			}
		}
		break;
	case TF_PICKSTONE:
		if(sd) {
			int eflag;
			struct item item_tmp(7049);
			block_list tbl;
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			clif_takeitem(*sd,tbl);
			eflag = pc_additem(*sd,item_tmp,1);
			if(eflag)
			{
				clif_additem(*sd,0,0,eflag);
				flooritem_data::create(item_tmp,1,sd->block_list::m,sd->block_list::x,sd->block_list::y,NULL,NULL,NULL,0);
			}
		}
		break;

	case RG_STRIPWEAPON:		// �X�g���b�v�E�F�|��
	case RG_STRIPSHIELD:		// �X�g���b�v�V�[���h
	case RG_STRIPARMOR:			// �X�g���b�v�A�[�}�[
	case RG_STRIPHELM:			// �X�g���b�v�w����
	case ST_FULLSTRIP:	
	{
		int strip_fix, equip = 0;
		int sclist[4] = {0,0,0,0};

		if (skillid == RG_STRIPWEAPON || skillid == ST_FULLSTRIP)
		   equip |= EQP_WEAPON;
		if (skillid == RG_STRIPSHIELD || skillid == ST_FULLSTRIP)
		   equip |= EQP_SHIELD;
		if (skillid == RG_STRIPARMOR || skillid == ST_FULLSTRIP)
		   equip |= EQP_ARMOR;
		if (skillid == RG_STRIPHELM || skillid == ST_FULLSTRIP)
		   equip |= EQP_HELM;

		strip_fix = src->get_dex() - bl->get_dex();
		if(strip_fix < 0)
			strip_fix=0;
		if (rand()%100 >= 5+2*skilllv+strip_fix/5)
		{
			if (sd)
				sd->skill_failed(skillid);
			break;
		}
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);

		if (dstsd)
		{
			for (i=0;i<MAX_EQUIP;++i)
			{
				if (dstsd->equip_index[i] < MAX_INVENTORY && dstsd->inventory_data[dstsd->equip_index[i]]) {
					if( equip &EQP_WEAPON && 
						(i == 9 || (i == 8 && dstsd->inventory_data[dstsd->equip_index[8]]->type == 4)) && 
						!(dstsd->unstripable_equip &EQP_WEAPON) && 
						!bl->has_status(SC_CP_WEAPON))
					{
						sclist[0] = SC_STRIPWEAPON; // Okay, we found a weapon to strip - It can be a right-hand, left-hand or two-handed weapon
						pc_unequipitem(*dstsd,dstsd->equip_index[i],3);
					}
					else if(equip &EQP_SHIELD && i == 8 && 
						dstsd->inventory_data[dstsd->equip_index[8]]->type == 5 && 
						!(dstsd->unstripable_equip &EQP_SHIELD) && 
						!bl->has_status(SC_CP_SHIELD))
					{
						sclist[1] = SC_STRIPSHIELD; // Okay, we found a shield to strip - It is really a shield, not a two-handed weapon or a left-hand weapon
						pc_unequipitem(*dstsd,dstsd->equip_index[i],3);
					}
					if( equip&EQP_ARMOR && i == 7 && 
						!(dstsd->unstripable_equip&EQP_ARMOR) && 
						!bl->has_status(SC_CP_ARMOR))
					{
						sclist[2] = SC_STRIPARMOR; // Okay, we found an armor to strip
						pc_unequipitem(*dstsd,dstsd->equip_index[i],3);
					}
					if( equip&EQP_HELM && i == 6 && 
						!(dstsd->unstripable_equip&EQP_HELM) && 
						!bl->has_status(SC_CP_HELM))
					{
						sclist[3] = SC_STRIPHELM; // Okay, we found a helm to strip
						pc_unequipitem(*dstsd,dstsd->equip_index[i],3);
					}
				}
			}
		}
		else if (dstmd)
		{
			if (equip &EQP_WEAPON)
				sclist[0] = SC_STRIPWEAPON;
			if (equip &EQP_SHIELD)
				sclist[1] = SC_STRIPSHIELD;
			if (equip &EQP_ARMOR)
				sclist[2] = SC_STRIPARMOR;
			if (equip &EQP_HELM)
				sclist[3] = SC_STRIPHELM;
		}

		for(i=0; i<4; ++i)
		{
			if (sclist[i] != 0) // Start the SC only if an equipment was stripped from this location
			   status_change_start(bl,(status_t)sclist[i],skilllv,0,0,0,skill_get_time(skillid,skilllv)+strip_fix/2,0);
		}

		break;
	}
	// PotionPitcher
	case AM_POTIONPITCHER:		// �|?�V�����s�b�`��?
		{
			block_list tbl;
			int x,hp = 0,sp = 0;
			if(sd) {
				x = skilllv%11 - 1;
				i = pc_search_inventory(*sd,skill_db[skillid].itemid[x]);
				if( i<0 || skill_db[skillid].itemid[x]<=0 ||
					sd->inventory_data[i] == NULL || sd->status.inventory[i].amount < skill_db[skillid].amount[x] ||
					sd->inventory_data[i]->use_script==NULL || sd->inventory_data[i]->use_script->script==NULL )
				{
					sd->skill_failed(skillid);
					block_list::freeblock_unlock();
					return 1;
				}
				sd->state.potion_flag = 1;
				sd->potion_hp = sd->potion_sp = sd->potion_per_hp = sd->potion_per_sp = 0;
				sd->skilltarget = bl->id;
				CScriptEngine::run(sd->inventory_data[i]->use_script->script,0,sd->block_list::id,0);
				pc_delitem(*sd,i,skill_db[skillid].amount[x],0);
				sd->state.potion_flag = 0;
				if(sd->potion_per_hp > 0 || sd->potion_per_sp > 0) {
					hp = bl->get_max_hp() * sd->potion_per_hp / 100;
					hp = hp * (100 + sd->skill_check(AM_POTIONPITCHER)*10 + sd->skill_check(AM_LEARNINGPOTION)*5)/100;
					if(dstsd) {
						sp = dstsd->status.max_sp * sd->potion_per_sp / 100;
						sp = sp * (100 + sd->skill_check(AM_POTIONPITCHER)*10 + sd->skill_check(AM_LEARNINGPOTION)*5)/100;
					}
				}
				else {
					if(sd->potion_hp > 0) {
						hp = sd->potion_hp * (100 + sd->skill_check(AM_POTIONPITCHER)*10 + sd->skill_check(AM_LEARNINGPOTION)*5)/100;
						hp = hp * (100 + (bl->get_vit()<<1)) / 100;
						if(dstsd)
							hp = hp * (100 + dstsd->skill_check(SM_RECOVERY)*10) / 100;
					}
					if(sd->potion_sp > 0) {
						sp = sd->potion_sp * (100 + sd->skill_check(AM_POTIONPITCHER)*10 + sd->skill_check(AM_LEARNINGPOTION)*5)/100;
						sp = sp * (100 + (bl->get_int()<<1)) / 100;
						if(dstsd)
							sp = sp * (100 + dstsd->skill_check(MG_SRECOVERY)*10) / 100;
					}
				}
			}
			else {
				hp = (1 + rand()%400) * (100 + skilllv*10) / 100;
				hp = hp * (100 + (bl->get_vit()<<1)) / 100;
				if(dstsd)
					hp = hp * (100 + dstsd->skill_check(SM_RECOVERY)*10) / 100;
			}
			tbl.id = 0;
			tbl.m = src->m;
			tbl.x = src->x;
			tbl.y = src->y;
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if(hp > 0 || (hp <= 0 && sp <= 0))
				clif_skill_nodamage(tbl,*bl,AL_HEAL,hp,1);
			if(sp > 0)
				clif_skill_nodamage(tbl,*bl,MG_SRECOVERY,sp,1);
			battle_heal(src,bl,hp,sp,0);
		}
		break;
	case AM_CP_WEAPON:
	case AM_CP_SHIELD:
	case AM_CP_ARMOR:
	case AM_CP_HELM:
		{
			status_t scid = (status_t)(SC_STRIPWEAPON + (skillid - AM_CP_WEAPON));
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if( bl->has_status(scid) )
				status_change_end(bl, scid, -1 );
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		}
		break;

	case SA_DISPELL:			// �f�B�X�y��
		{
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			
			if(status_isimmune(bl))
				break;

			if(rand()%100 >= 50+10*skilllv-sc_def_mdef)
			{
				if (sd)
					sd->skill_failed(skillid);
				break;
			}
			for(i=0;i<136;++i){
				if( i==SC_RIDING || i==SC_FALCON || i==SC_HALLUCINATION || i==SC_WEIGHT50 || i==SC_WEIGHT90 || 
					i==SC_STRIPWEAPON || i==SC_STRIPSHIELD || i==SC_STRIPARMOR || i==SC_STRIPHELM || 
					i==SC_CP_WEAPON || i==SC_CP_SHIELD || i==SC_CP_ARMOR || i==SC_CP_HELM || 
					i==SC_COMBO || i==SC_LULLABY || i==SC_RICHMANKIM || i==SC_ETERNALCHAOS || 
					i==SC_DRUMBATTLE || i==SC_NIBELUNGEN || i==SC_ROKISWEIL || i==SC_INTOABYSS || 
					i==SC_SIEGFRIED || i==SC_DISSONANCE || i==SC_WHISTLE || i==SC_ASSNCROS || 
					i==SC_POEMBRAGI || i==SC_APPLEIDUN || i==SC_UGLYDANCE || i==SC_HUMMING || 
					i==SC_DONTFORGETME || i==SC_FORTUNE || i==SC_SERVICE4U || 
					i==SC_MOONLIT || i==SC_LONGING || i==SC_HERMODE || i== SC_DANCING || 
					i==SC_GUILDAURA || i==SC_STEELBODY || i==SC_EDP)
						continue;
				status_change_end(bl,(status_t)i,-1);
			}
		}
		break;

	case TF_BACKSLIDING:		// �o�b�N�X�e�b�v
		src->stop_walking(1);
		skill_blown(src,bl,skill_get_blewcount(skillid,skilllv)|0x10000);
		clif_fixobject(*src);
		skill_addtimerskill(src,tick + 200,src->id,0,0,skillid,skilllv,0,flag);
		break;

	case SA_CASTCANCEL:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		skill_castcancel(src,1);
		if(sd) {
			int sp = skill_get_sp(sd->skillid_old,sd->skilllv_old);
			sp = sp * (90 - (skilllv-1)*20) / 100;
			if(sp < 0) sp = 0;
			sd->heal(0,-sp);
		}
		break;
	case SA_SPELLBREAKER:	// �X�y���u���C�J?
		{
			int sp;
			if(bl->has_status(SC_MAGICROD))
			{
				if(dstsd) {
					sp = skill_get_sp(skillid,skilllv);
					sp = sp * bl->get_statusvalue2(SC_MAGICROD).integer() / 100;
					if(sp > 0x7fff) sp = 0x7fff;
					else if(sp < 1) sp = 1;
					if(dstsd->status.sp + sp > dstsd->status.max_sp) {
						sp = dstsd->status.max_sp - dstsd->status.sp;
						dstsd->status.sp = dstsd->status.max_sp;
					}
					else
						dstsd->status.sp += sp;
					clif_heal(dstsd->fd,SP_SP,sp);
				}
				clif_skill_nodamage(*bl,*bl,SA_MAGICROD,(unsigned short)bl->get_statusvalue1(SC_MAGICROD).integer(),1);
				if(sd) {
					sp = sd->status.max_sp/5;
					if(sp < 1) sp = 1;
					sd->heal(0,-sp);
				}
			}
			else {
				int bl_skillid=0,bl_skilllv=0,hp=0;
				if(*bl == BL_PC) {
					if(dstsd && dstsd->skilltimer != -1) {
						bl_skillid = dstsd->skillid;
						bl_skilllv = dstsd->skilllv;
					}
				}
				else if(*bl == BL_MOB) {
					if(dstmd && dstmd->skilltimer != -1) {
						if( bl->get_mode() & 0x20 )
						{	//Only 10% success chance against bosses. [Skotlex]
							if (rand()%100 < 90)
							{
								sd->skill_failed(skillid);
								break;
							}
						} else
							hp = bl->get_max_hp()/50; //Recover 2% HP [Skotlex]
						bl_skillid = dstmd->skillid;
						bl_skilllv = dstmd->skilllv;
						if (maps[bl->m].flag.pvp || maps[bl->m].flag.gvg)
							hp = bl->get_max_hp()/50; //Recover 2% HP [Skotlex]
					}
				}
				if(bl_skillid > 0 && skill_db[bl_skillid].skill_type == BF_MAGIC) {
					clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
					skill_castcancel(bl,0);
					sp = skill_get_sp(bl_skillid,bl_skilllv);
					if(dstsd)
						dstsd->heal(-hp,-sp);
					if(sd) {
						sp = sp*(25*(skilllv-1))/100;
						if(skilllv > 1 && sp < 1) sp = 1;
						if(sp > 0x7fff) sp = 0x7fff;
						else if(sp < 1) sp = 1;
						if(sd->status.sp + sp > sd->status.max_sp) {
							sp = sd->status.max_sp - sd->status.sp;
							sd->status.sp = sd->status.max_sp;
						}
						else
							sd->status.sp += sp;
						if (hp && skilllv > 5)
						{	//Recover half damaged HP at levels 6-10 [Skotlex]
							hp /=2;
							if(sd->status.hp + hp > sd->status.max_hp) {
								hp = sd->status.max_hp - sd->status.hp;
								sd->status.hp = sd->status.max_hp;
							}
							else
								sd->status.hp += hp;

							clif_heal(sd->fd,SP_HP,hp);
						}
						clif_heal(sd->fd,SP_SP,sp);
					}
				}
				else if(sd)
					sd->skill_failed(skillid);
			}
		}
		break;
	case SA_MAGICROD:
		if (status_isimmune(bl))
			break;
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;
	case SA_AUTOSPELL:			// �I?�g�X�y��
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(sd)
			clif_autospell(*sd,skilllv);
		else {
			int maxlv=1,spellid=0;
			static const int spellarray[3] = { MG_COLDBOLT,MG_FIREBOLT,MG_LIGHTNINGBOLT };
			if(skilllv >= 10) {
				spellid = MG_FROSTDIVER;
				maxlv = skilllv - 9;
			}
			else if(skilllv >=8) {
				spellid = MG_FIREBALL;
				maxlv = skilllv - 7;
			}
			else if(skilllv >=5) {
				spellid = MG_SOULSTRIKE;
				maxlv = skilllv - 4;
			}
			else if(skilllv >=2) {
				spellid = spellarray[rand()%3];
				maxlv = skilllv - 1;
			}
			else if(skilllv > 0) {
				spellid = MG_NAPALMBEAT;
				maxlv = 3;
			}
			if(spellid > 0)
				status_change_start(src,SC_AUTOSPELL,skilllv,spellid,maxlv,0,
					skill_get_time(SA_AUTOSPELL,skilllv),0);
		}
		break;

	// �����_��?��?���A��?��?���A�n�A�΁A��
	case NPC_ATTRICHANGE:
	case NPC_CHANGEWATER:
	case NPC_CHANGEGROUND:
	case NPC_CHANGEFIRE:
	case NPC_CHANGEWIND:
	// �ŁA���A�O�A��
	case NPC_CHANGEPOISON:
	case NPC_CHANGEHOLY:
	case NPC_CHANGEDARKNESS:
	case NPC_CHANGETELEKINESIS:
	case NPC_CHANGEUNDEAD:
		if(md){
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			md->def_ele = skill_get_pl(skillid);
			if (md->def_ele == 0)			// �����_��?���A�������A
				md->def_ele = rand()%10;	// �s��?���͏���
			md->def_ele += (1+rand()%4)*20;	// ?�����x���̓����_��
		}
		break;

	case NPC_PROVOCATION:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(md)
			clif_pet_performance(*src,mob_db[md->class_].skill[md->skillidx].val[0]);
		break;

	case NPC_HALLUCINATION:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(status_isimmune(bl))
			break;
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;

	case NPC_KEEPING:
	case NPC_BARRIER:
		{
			int skill_time = skill_get_time(skillid,skilllv);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_time,0 );
			if (md)
				md->set_delay(tick + skill_time);
			else if (sd)
				sd->set_delay(tick + skill_time);
		}
		break;

	case NPC_REBIRTH:
		if( md && md->is_dead() )
			md->set_spawndelay();
		break;

	case NPC_DARKBLESSING:
		{
			int sc_def = 100 - status_get_mdef(bl);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if(status_isimmune(bl))
				break;
			if(status_get_elem_type(bl) == 7 || bl->get_race() == 6)
				break;
			if(rand()%100 < sc_def*(50+skilllv*5)/100) {
				if(dstsd)
				{
					int hp = bl->get_hp()-1;
					dstsd->heal(-hp,0);
				}
				else if(dstmd)
					dstmd->hp = 1;
			}
		}
		break;

	case NPC_LICK:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if (dstsd) {
			if(dstsd->state.no_weapon_damage )
				break;
			dstsd->heal(0,-100);
		}
		if(rand()%100 < (skilllv*5)*sc_def_vit/100)
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
		break;

	case NPC_SUICIDE:			// ����
		if(src && bl){
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if (md)
				mob_damage(*md,md->hp,0,NULL);
			else if (sd)
				pc_damage(*sd,sd->status.hp,NULL);
		}
		break;

	case NPC_SUMMONSLAVE:		// �艺����
	case NPC_SUMMONMONSTER:		// MOB����
		if(md)
			md->summon_slaves(skillid, skilllv);
		break;

	case NPC_CALLSLAVE:		//��芪���Ăі߂�
		if(md)
		{	//mob.c��[��芪�������X�^�[�̏���]�ŗ��p
			md->recallmob_count = md->count_slaves();
			md->state.recall_flag = (md->recallmob_count>0);
		}
		break;

	case NPC_RANDOMMOVE:
		if( md && mob_db[md->class_].mode&1 && md->is_movable() &&
			(md->master_id == 0 || md->state.special_mob_ai || md->master_dist > 10) &&
			DIFF_TICK(md->next_walktime, tick) > 7000 && md->walkpath.finished() )
		{
			md->next_walktime = tick + 3000 * rand() % 2000;
			md->randomwalk(tick);
		}
		break;
	
	case NPC_SPEEDUP:
		{
			// or does it increase casting rate? just a guess xD
			i = SC_SPEEDPOTION0 + skilllv - 1;
			if (i > SC_SPEEDPOTION3)
				i = SC_SPEEDPOTION3;
			status_change_start(bl,(status_t)i,skilllv,0,0,0,skilllv * 60000,0);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;

	case NPC_REVENGE:
		// not really needed... but adding here anyway ^^
		if (md && md->master_id > 0)
		{
			block_list *mbl, *tbl;
			if ((mbl = block_list::from_blid(md->master_id)) == NULL ||
				(tbl = battle_gettargeted(*mbl)) == NULL)
				break;
			md->provoke_id = tbl->id;
			mob_target(*md, tbl, mob_db[md->class_].range);
		}
		break;

	case NPC_STOP:
		if (md && md->target_id > 0) {
			md->unlock_target(tick);
		}
		if(dstsd) {
			dstsd->stop_walking(1);
		    dstsd->canmove_tick += skill_get_time(skillid,skilllv);
		} else if(dstmd) {
			dstmd->stop_walking(1);
		    dstmd->canmove_tick += skill_get_time(skillid,skilllv);
		}
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		break;

	case NPC_RUN:		//���
		if(md) {
			int dist = skilllv;//��ނ��鋗��
			int dir = md->dir; //�������ǂ̕����Ɍ����Ă邩�`�F�b�N
			static const signed char mask[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};

			md->attacked_id = 0;
			md->attacked_count = 0;
			md->target_id = 0;
			md->state.targettype = NONE_ATTACKABLE;
			md->state.skillstate = MSS_IDLE;			
			md->walktoxy(md->block_list::x + dist * mask[dir][0], md->block_list::y + dist * mask[dir][1]);
		}
		break;

	case NPC_TRANSFORMATION:
	case NPC_METAMORPHOSIS:
		if(md)
			mob_class_change(*md, mob_db[md->class_].skill[md->skillidx].val,0); // count=0 to have the array size checked internally
		break;

	case NPC_EMOTION:			// �G��?�V����
		if(md)
			clif_emotion(*md,mob_db[md->class_].skill[md->skillidx].val[0]);
		break;

	case NPC_EMOTION_ON:
		// not sure what it does
		break;

	case NPC_DEFENDER:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		break;

	// Equipment breaking monster skills [Celest]
	case NPC_BREAKWEAPON:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(dstsd && config.equip_skill_break_rate)
			pc_breakweapon(*dstsd);
		break;

	case NPC_BREAKARMOR:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(dstsd && config.equip_skill_break_rate)
			pc_breakarmor(*dstsd);
		break;

	case NPC_BREAKHELM:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(dstsd && config.equip_skill_break_rate)
			pc_breakhelm(*dstsd);
		break;

	case NPC_BREAKSHIELD:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(dstsd && config.equip_skill_break_rate)
			pc_breakshield(*dstsd);
		break;

	case NPC_POWERUP:	//NPC�����g��
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		status_change_start(bl,SC_EXPLOSIONSPIRITS,skilllv,0,0,0,skilllv * 60000,0);
		// another random guess xP
		status_change_start(bl,SC_INCALLSTATUS,skilllv * 5,0,0,0,skilllv * 60000,0);
		break;

	case NPC_AGIUP:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		status_change_start(bl,SC_INCAGI,skilllv * 10,0,0,0,skilllv * 60000,0);
		break;

	case NPC_SIEGEMODE:
	case NPC_INVISIBLE:
		// not sure what it does
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		break;

	case WE_MALE:				// �N�����͌���
		if(sd && dstsd){
			int hp_rate=(skilllv <= 0)? 0:skill_db[skillid].hp_rate[skilllv-1];
			int gain_hp=dstsd->status.max_hp*abs(hp_rate)/100;// 15%
			battle_heal(NULL,bl,gain_hp,0,0);
			clif_skill_nodamage(*src,*bl,skillid,gain_hp,1);
		}
		break;
	case WE_FEMALE:				// ���Ȃ���?��?���ɂȂ�܂�
		if(sd && dstsd){
			int sp_rate=(skilllv <= 0)? 0:skill_db[skillid].sp_rate[skilllv-1];
			int gain_sp=dstsd->status.max_sp*abs(sp_rate)/100;// 15%
			battle_heal(NULL,bl,0,gain_sp,0);
			clif_skill_nodamage(*src,*bl,skillid,gain_sp,1);
		}
		break;

	case WE_CALLPARTNER:			// ���Ȃ���?������
		if(sd)
		{
			if((dstsd = pc_get_partner(*sd)) == NULL)
			{
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			if(maps[sd->block_list::m].flag.nomemo || maps[sd->block_list::m].flag.nowarpto || maps[dstsd->block_list::m].flag.nowarp){
				clif_skill_teleportmessage(*sd,1);
				block_list::freeblock_unlock();
				return 0;
			}
			skill_unitsetting(src,skillid,skilllv,sd->block_list::x,sd->block_list::y,0);
		}
		break;

// parent-baby skills
	case WE_BABY:
		if(sd){
			map_session_data *f_sd = pc_get_father(*sd);
			map_session_data *m_sd = pc_get_mother(*sd);
			// if neither was found
			if(!f_sd && !m_sd){
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			status_change_start(bl,SC_STUN,skilllv,0,0,0,skill_get_time2(skillid,skilllv),0);
			if (f_sd) status_change_start(f_sd,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
			if (m_sd) status_change_start(m_sd,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		}
		break;

	case WE_CALLPARENT:
		if(sd){
			map_session_data *f_sd = pc_get_father(*sd);
			map_session_data *m_sd = pc_get_mother(*sd);
			// if neither was found
			if(!f_sd && !m_sd){
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			if(maps[sd->block_list::m].flag.nomemo || maps[sd->block_list::m].flag.nowarpto){
				clif_skill_teleportmessage(*sd,1);
				block_list::freeblock_unlock();
				return 0;
			}
			if( (!f_sd && m_sd && maps[m_sd->block_list::m].flag.nowarp) ||
				(!m_sd && f_sd && maps[f_sd->block_list::m].flag.nowarp) ||
				(f_sd && maps[f_sd->block_list::m].flag.nowarp && m_sd && maps[m_sd->block_list::m].flag.nowarp) )
			{	//Case where neither one can be warped.
				clif_skill_teleportmessage(*sd,1);
				block_list::freeblock_unlock();
				return 0;
			}
			//Warp those that can be warped.
			if(f_sd && !maps[f_sd->block_list::m].flag.nowarp) pc_setpos(*f_sd,maps[sd->block_list::m].mapname,sd->block_list::x,sd->block_list::y,3);
			if(m_sd && !maps[m_sd->block_list::m].flag.nowarp) pc_setpos(*m_sd,maps[sd->block_list::m].mapname,sd->block_list::x,sd->block_list::y,3);
		}
		break;

	case WE_CALLBABY:
		if(sd){
			if((dstsd = pc_get_child(*sd)) == NULL){
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			if(maps[sd->block_list::m].flag.nomemo || maps[sd->block_list::m].flag.nowarpto || maps[dstsd->block_list::m].flag.nowarp){
				clif_skill_teleportmessage(*sd,1);
				block_list::freeblock_unlock();
				return 0;
			}
			pc_setpos(*dstsd,maps[sd->block_list::m].mapname,sd->block_list::x,sd->block_list::y,3);
		}
		break;

	case PF_HPCONVERSION:			// ���C�t�u������
		clif_skill_nodamage(*src, *bl, skillid, skilllv, 1);
		if (sd) {
			int hp, sp;
			hp = sd->status.max_hp / 10; //��{��HP��10%
			sp = hp * 10 * skilllv / 100;
			if (sd->status.sp + sp > sd->status.max_sp)
				sp = sd->status.max_sp - sd->status.sp;
			// we need to check with the sp that was taken away when casting too
			if (sd->status.sp + skill_get_sp(skillid, skilllv) >= sd->status.max_sp)
				hp = sp = 0;
			sd->heal(-hp, sp);
			clif_heal(sd->fd, SP_SP, sp);
			clif_updatestatus(*sd, SP_SP);
		}
		break;
	case HT_REMOVETRAP:				// ����?�u�g���b�v
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		{
			struct skill_unit *su=NULL;
			int myflag;
			if((*bl==BL_SKILL) &&
			   (su=(struct skill_unit *)bl) &&
			   (su->group->src_id == src->id || maps[bl->m].flag.pvp || maps[bl->m].flag.gvg) &&
			   (su->group->unit_id >= 0x8f && su->group->unit_id <= 0x99) &&
			   (su->group->unit_id != UNT_VENOMDUST)){ //??d?a?e?O?�E
				if(sd)
				{
					if(config.skill_removetrap_type == 1)
					{
						for(i=0;i<10;++i)
						{
							if( skill_db[su->group->skill_id].itemid[i] > 0 )
							{
								struct item item_tmp( skill_db[su->group->skill_id].itemid[i] );
								if( item_tmp.nameid && (myflag=pc_additem(*sd,item_tmp,skill_db[su->group->skill_id].amount[i])))
								{
									clif_additem(*sd,0,0,myflag);
									flooritem_data::create(item_tmp,skill_db[su->group->skill_id].amount[i],sd->block_list::m,sd->block_list::x,sd->block_list::y,NULL,NULL,NULL,0);
								}
							}
						}
					}
					else
					{
						struct item item_tmp(1065);
						if(item_tmp.nameid && (myflag=pc_additem(*sd,item_tmp,1)))
						{
							clif_additem(*sd,0,0,myflag);
							flooritem_data::create(item_tmp,1,sd->block_list::m,sd->block_list::x,sd->block_list::y,NULL,NULL,NULL,0);
						}
					}
				}
				if(su->group->unit_id == UNT_ANKLESNARE && su->group->val2)
				{
					block_list *target=block_list::from_blid(su->group->val2);
					if(target && (*target== BL_PC || *target== BL_MOB))
						status_change_end(target,SC_ANKLE,-1);
				}
				skill_delunit(su);
			}
		}
		break;
	case HT_SPRINGTRAP:				// �X�v�����O�g���b�v
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		{
			struct skill_unit *su=NULL;
			if((*bl==BL_SKILL) && (su=(struct skill_unit *)bl) && (su->group) ){
				switch(su->group->unit_id){
					case UNT_ANKLESNARE:	// ankle snare
						if (su->group->val2 != 0)
							// if it is already trapping something don't spring it,
							// remove trap should be used instead
							break;
						// otherwise fallthrough to below
					case UNT_BLASTMINE:	// �u���X�g�}�C��
					case UNT_SKIDTRAP:	// �X�L�b�h�g���b�v
					case UNT_LANDMINE:	// �����h�}�C��
					case UNT_SHOCKWAVE:	// �V���b�N�E�F?�u�g���b�v
					case UNT_SANDMAN:	// �T���h�}��
					case UNT_FLASHER:	// �t���b�V��?
					case UNT_FREEZINGTRAP:	// �t��?�W���O�g���b�v
					case UNT_CLAYMORETRAP:	// �N���C���A?�g���b�v
					case UNT_TALKIEBOX:	// �g?�L?�{�b�N�X
						su->group->unit_id = UNT_USEDTRAP;
						clif_changelook(*bl,LOOK_BASE,su->group->unit_id);
						su->group->limit=DIFF_TICK(tick+1500,su->group->tick);
						su->limit=DIFF_TICK(tick+1500,su->group->tick);
				}
			}
		}
		break;
	case BD_ENCORE:					// �A���R?��
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		if(sd)
			skill_use_id(sd,src->id,sd->skillid_dance,sd->skilllv_dance);
		break;

	case AS_SPLASHER:		// �x�i���X�v���b�V��?
		if( bl->get_max_hp()*3 < 4*bl->get_hp() )
		{	//HP��3/4�ȏ�?���Ă����玸�s
			block_list::freeblock_unlock();
			return 1;
		}
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,skillid,src->id,skill_get_time(skillid,skilllv),1000,0 );
		break;

	case PF_MINDBREAKER:		// �v���{�b�N
		{
			// MVPmob�ƕs���ɂ�?���Ȃ�
			if((dstmd && bl->get_mode()&0x20) || bl->is_undead()) //�s���ɂ�?���Ȃ�
			{
				block_list::freeblock_unlock();
				return 1;
			}

			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			if (rand()%100 > 55 + skilllv*5)
			{	//Has a 55% + skilllv*5% success chance.
				if (sd)
					sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );

			if(dstmd && dstmd->skilltimer!=-1 && dstmd->state.skillcastcancel)	// �r���W�Q
				skill_castcancel(bl,0);
			if(dstsd && dstsd->skilltimer!=-1 && (!dstsd->state.no_castcancel || maps[bl->m].flag.gvg)
				&& dstsd->state.skillcastcancel	&& !dstsd->state.no_castcancel2)
				skill_castcancel(bl,0);

			if( bl->has_status(SC_FREEZE) )
				status_change_end(bl,SC_FREEZE,-1);
			if( bl->has_status(SC_STONE) && bl->get_statusvalue2(SC_STONE).integer()==0 )
				status_change_end(bl,SC_STONE,-1);
			if( bl->has_status(SC_SLEEP) )
				status_change_end(bl,SC_SLEEP,-1);

			if(dstmd)
				mob_target(*dstmd,src,skill_get_range(skillid,skilllv));
		}
		break;

	case PF_SOULCHANGE:
		{
			int sp1 = 0, sp2 = 0;
			if (sd) {
				if (dstsd) {
					sp1 = sd->status.sp > dstsd->status.max_sp ? dstsd->status.max_sp : sd->status.sp;
					sp2 = dstsd->status.sp > sd->status.max_sp ? sd->status.max_sp : dstsd->status.sp;
					sd->status.sp = sp2;
					dstsd->status.sp = sp1;
					clif_heal(sd->fd,SP_SP,sp2);
					clif_updatestatus(*sd,SP_SP);
					clif_heal(dstsd->fd,SP_SP,sp1);
					clif_updatestatus(*dstsd,SP_SP);
				} else if (dstmd) {
					if (dstmd->state.soul_change_flag) {
						sd->skill_failed(skillid);
						block_list::freeblock_unlock();
						return 0;
					}
					sp2 = sd->status.max_sp * 3 /100;
					if (sd->status.sp + sp2 > sd->status.max_sp)
						sp2 = sd->status.max_sp - sd->status.sp;
					sd->status.sp += sp2;
					clif_heal(sd->fd,SP_SP,sp2);
					clif_updatestatus(*sd,SP_SP);
					dstmd->state.soul_change_flag = 1;
				}
			}
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;

	// Slim Pitcher
	case CR_SLIMPITCHER:
		{
			if (sd && flag&1) {
				block_list tbl;
				int hp = sd->potion_hp * (100 + sd->skill_check(CR_SLIMPITCHER)*10 + sd->skill_check(AM_POTIONPITCHER)*10 + sd->skill_check(AM_LEARNINGPOTION)*5)/100;
				hp = hp * (100 + (bl->get_vit()<<1))/100;
				if (dstsd) {
					hp = hp * (100 + dstsd->skill_check(SM_RECOVERY)*10)/100;
				}
				tbl.id = 0;
				tbl.m = src->m;
				tbl.x = src->x;
				tbl.y = src->y;
				clif_skill_nodamage(tbl,*bl,AL_HEAL,hp,1);
				battle_heal(NULL,bl,hp,0,0);
			}
		}
		break;
	// Full Chemical Protection
	case CR_FULLPROTECTION:
		{
			int skilltime;
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			skilltime = skill_get_time(skillid,skilllv);
			for (i=0; i<4; ++i)
			{
				if( bl->has_status( (status_t)(SC_STRIPWEAPON+i) ) )
					status_change_end(bl, (status_t)(SC_STRIPWEAPON + i), -1 );
				status_change_start(bl,(status_t)(SC_CP_WEAPON + i),skilllv,0,0,0,skilltime,0 );
			}
		}
		break;

	case RG_CLEANER:
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		break;

	case ST_PRESERVE:
		if (sd)
		{
			if(	sd->has_status(SC_PRESERVE) )
				status_change_end(src, SC_PRESERVE, -1 );
			else
				status_change_start(src,SC_PRESERVE,skilllv,0,0,0,skill_get_time(skillid, skilllv),0 );
			clif_skill_nodamage(*src,*src,skillid,skilllv,1);
		}
		break;

	case PF_DOUBLECASTING:
		if (rand() % 100 > 30 + skilllv * 10) {
			sd->skill_failed(skillid);
			block_list::freeblock_unlock();
			return 0;
		}
		clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		status_change_start(bl,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0 );
		break;

	case CG_LONGINGFREEDOM:
		if( !src->has_status(SC_LONGING) && src->has_status(SC_DANCING) &&
			skill_get_unit_flag(src->get_statusvalue1(SC_DANCING).integer())&UF_ENSEMBLE) {
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
			status_change_start(src,(status_t)SkillStatusChangeTable[skillid],skilllv,0,0,0,skill_get_time(skillid,skilllv),0);
		}
		break;

	case CG_TAROTCARD:
		{
			int eff, count = 1;
			if (rand() % 100 > skilllv * 8) {
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			do {
				eff = rand() % 14;
				clif_specialeffect(*bl, 523 + eff, 0);
				switch (eff)
				{
				case 0:	// heals SP to 0
					if (dstsd) dstsd->heal(0,-dstsd->status.sp);
					break;
				case 1:	// matk halved
					status_change_start(bl,SC_INCMATK2,-50,0,0,0,30000,0);
					break;
				case 2:	// all buffs removed
					status_change_clear_buffs(bl);
					break;
				case 3:	// 1000 damage, random armor destroyed
					{
						int where[] = { EQP_ARMOR, EQP_SHIELD, EQP_HELM };
						battle_damage(src, bl, 1000, 0);
						clif_damage(*src,*bl,tick,0,0,1000,0,0,0);
						if (dstsd) pc_break_equip(*dstsd, where[rand() % 3]);
					}
					break;
				case 4:	// atk halved
					status_change_start(bl,SC_INCATK2,-50,0,0,0,30000,0);
					break;
				case 5:	// 2000HP heal, random teleported
					if(sd) sd->heal(2000,0);
					if(bl->is_on_map() )
					{
						if(sd && !maps[src->m].flag.noteleport) pc_setpos(*sd,sd->mapname,0xFFFF,0xFFFF, 3);
						else if(md && !maps[src->m].flag.monster_noteleport) mob_warp(*md,-1,-1,-1,3);
					}
					break;
				case 6:	// random 2 other effects
					count = 3;
					break;
				case 7:	// stun freeze or stoned
					status_change_start(bl,SC_STUN,skilllv,0,0,0,30000,0);
					status_change_start(bl,SC_FREEZE,skilllv,0,0,0,30000,0);
					status_change_start(bl,SC_STONE,skilllv,0,0,0,30000,0);
					break;
				case 8:	// curse coma or poison
					status_change_start(bl,SC_CURSE,skilllv,0,0,0,30000,0);
					//status_change_start(bl,SC_COMA,skilllv,0,0,0,30000,0);
					status_change_start(bl,SC_POISON,skilllv,0,0,0,30000,0);
					break;
				case 9:	// chaos
					status_change_start(bl,SC_CONFUSION,skilllv,0,0,0,30000,0);
					break;
				case 10:	// 6666 damage, atk matk halved, cursed
					battle_damage(src, bl, 6666, 0);
					clif_damage(*src,*bl,tick,0,0,6666,0,0,0);
					status_change_start(bl,SC_INCATK2,-50,0,0,0,30000,0);
					status_change_start(bl,SC_INCMATK2,-50,0,0,0,30000,0);
					status_change_start(bl,SC_CURSE,skilllv,0,0,0,30000,0);
					break;
				case 11:	// 4444 damage
					battle_damage(src, bl, 4444, 0);
					clif_damage(*src,*bl,tick,0,0,4444,0,0,0);
					break;
				case 12:	// stun
					status_change_start(bl,SC_STUN,skilllv,0,0,0,5000,0);
					break;
				case 13:	// atk,matk,hit,flee,def reduced
					status_change_start(bl,SC_INCATK2,-20,0,0,0,30000,0);
					status_change_start(bl,SC_INCMATK2,-20,0,0,0,30000,0);
					status_change_start(bl,SC_INCHIT2,-20,0,0,0,30000,0);
					status_change_start(bl,SC_INCFLEE2,-20,0,0,0,30000,0);
					status_change_start(bl,SC_INCDEF2,-20,0,0,0,30000,0);
					break;
				default:
					break;			
				}			
			} while ((--count) > 0);
			clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
		}
		break;

	// New guild skills [Celest]
	case GD_BATTLEORDER:
		{
			struct guild *g = NULL;
			// Only usable during WoE
			if (!agit_flag) {
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			if(flag&1) {
				if (dstsd && dstsd->status.guild_id == sd->status.guild_id)	{
					status_change_start(dstsd,SC_BATTLEORDERS,skilllv,0,0,0,0,0 );
				}
			}
			else if (sd && sd->status.guild_id > 0 && (g = guild_search(sd->status.guild_id)) &&
				strcmp(sd->status.name,g->master)==0) {
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);

				maps[src->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ALL|1,skill_castend_nodamage_id),
					src->x, src->y, 15, BL_ALL);
				pc_blockskill_start(*sd, skillid, 300000);
			}
		}
		break;
	case GD_REGENERATION:
		{
			struct guild *g = NULL;
			// Only usable during WoE
			if (!agit_flag) {
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			if(flag&1) {
				if (dstsd && dstsd->status.guild_id == sd->status.guild_id)	{
					status_change_start(dstsd,SC_REGENERATION,skilllv,0,0,0,0,0 );
				}
			}
			else if (sd && sd->status.guild_id > 0 && (g = guild_search(sd->status.guild_id)) &&
				strcmp(sd->status.name,g->master)==0) {
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);

				maps[src->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ALL|1,skill_castend_nodamage_id),
					src->x, src->y, 15, BL_ALL);
				
				pc_blockskill_start(*sd, skillid, 300000);
			}
		}
		break;
	case GD_RESTORE:
		{
			struct guild *g = NULL;
			// Only usable during WoE
			if (!agit_flag) {
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			if(flag&1) {
				if (dstsd && dstsd->status.guild_id == sd->status.guild_id)	{
					int hp, sp;
					hp = dstsd->status.max_hp*9/10;
					sp = dstsd->status.max_sp*9/10;
					sp = dstsd->status.sp + sp <= dstsd->status.max_sp ? sp : dstsd->status.max_sp - dstsd->status.sp;
					clif_skill_nodamage(*src,*bl,AL_HEAL,hp,1);
					battle_heal(NULL,bl,hp,sp,0);
				}
			}
			else if (sd && sd->status.guild_id > 0 && (g = guild_search(sd->status.guild_id)) &&
				strcmp(sd->status.name,g->master)==0) {
				clif_skill_nodamage(*src,*bl,skillid,skilllv,1);

				maps[src->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick, flag|BCT_ALL|1,skill_castend_nodamage_id),
					src->x, src->y, 15, BL_ALL);
				pc_blockskill_start(*sd, skillid, 300000);
			}
		}
		break;
	case GD_EMERGENCYCALL:
		{
			int dx[9]={-1, 1, 0, 0,-1, 1,-1, 1, 0};
			int dy[9]={ 0, 0, 1,-1, 1,-1,-1, 1, 0};
			int j = 0;
			struct guild *g = NULL;
			// Only usable during WoE
			if (!agit_flag ||
				(sd && maps[sd->block_list::m].flag.nowarpto &&	// if not allowed to warp to the map
				guild_mapname2gc(sd->mapname) == NULL)) {	// and it's not a castle...
				sd->skill_failed(skillid);
				block_list::freeblock_unlock();
				return 0;
			}
			// i don't know if it actually summons in a circle, but oh well. ;P
			if (sd && sd->status.guild_id > 0 && (g = guild_search(sd->status.guild_id)) &&
				strcmp(sd->status.name,g->master)==0) {
				for(i = 0; i < g->max_member; ++i, ++j) {
					if (j>8) j=0;
					if ((dstsd = g->member[i].sd) != NULL && sd != dstsd) {
						 if (maps[dstsd->block_list::m].flag.nowarp &&
							 guild_mapname2gc(sd->mapname) == NULL)
							 continue;
						clif_skill_nodamage(*src,*bl,skillid,skilllv,1);
						if( !maps[sd->block_list::m].is_passable(sd->block_list::x+dx[j],sd->block_list::y+dy[j]) )
							dx[j] = dy[j] = 0;
						pc_setpos(*dstsd, sd->mapname, sd->block_list::x+dx[j], sd->block_list::y+dy[j], 2);
					}
				}
				pc_blockskill_start(*sd, skillid, 300000);
			}
		}
		break;

	default:
		ShowMessage("Unknown skill used (skill_castend_nodamage_id):%d\n",skillid);
		block_list::freeblock_unlock();
		return 1;
	}

	block_list::freeblock_unlock();
	return 0;
}

/*==========================================
 * �X�L���g�p�i�r�������AID�w��j
 *------------------------------------------
 */
int skill_castend_id(int tid, unsigned long tick, int id, basics::numptr data)
{
	map_session_data* sd = map_session_data::from_blid(id);
	block_list *bl;
	int range,inf2;

	nullpo_retr(0, sd);

	if( !sd->is_on_map() )
		return 0;

	if(sd->skillid != SA_CASTCANCEL && sd->skilltimer != -1 && (range = sd->skill_check(SA_FREECAST)) > 0) //Hope ya don't mind me borrowing range :X
		status_calc_speed(*sd, SA_FREECAST, range, 0); 

	if(sd->skillid != SA_CASTCANCEL && sd->skilltimer != tid )	// �^�C�}ID�̊m�F
		return 0;

	if(sd->skillid == 0xFFFF || sd->skilllv == 0xFFFF)	// skill has failed after starting casting
	{
		sd->skilltimer = -1;
		return 0;
	}


	if(sd->skillid != SA_CASTCANCEL)
		sd->skilltimer=-1;

	if( (bl=block_list::from_blid(sd->skilltarget))==NULL || !bl->is_on_map() || sd->block_list::m != bl->m || sd->is_dead() )
	{	//�}�b�v���Ⴄ������������ł���
		sd->canact_tick = tick;
		sd->canmove_tick = tick;
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}

	if(sd->skillid == PR_LEXAETERNA)
	{
		if( bl->has_status(SC_FREEZE) || (bl->has_status(SC_STONE) && bl->get_statusvalue2(SC_STONE).integer() == 0) )
		{
			sd->skill_failed(sd->skillid);
			sd->canact_tick = tick;
			sd->canmove_tick = tick;
			sd->skillitem = sd->skillitemlv = 0xFFFF;
			return 0;
		}
	}
	else if(sd->skillid == RG_BACKSTAP) {
		dir_t dir = sd->get_direction(*bl);
		dir_t t_dir = bl->get_dir();
		int dist = distance(*sd,*bl);
		if( *bl!= BL_SKILL && (dist == 0 || !is_same_direction(dir,t_dir))) {
			sd->skill_failed(sd->skillid);
			sd->canact_tick = tick;
			sd->canmove_tick = tick;
			sd->skillitem = sd->skillitemlv = 0xFFFF;
			return 0;
		}
	}
	else if (sd->skillid == PR_LEXDIVINA)
	{
		if( battle_check_target(sd,bl, BCT_ENEMY)<=0 &&
			!bl->has_status(SC_SILENCE) )	//Prevent Casting Lex Divina on unsilenced chars. [Skotlex]
		{
			sd->canact_tick = tick;
			sd->canmove_tick = tick;
			sd->skillitem = sd->skillitemlv = 0xFFFF;
			return 0;
		}
	}

	inf2 = skill_get_inf2(sd->skillid);
	if( ( (skill_get_inf(sd->skillid)&INF_ATTACK_SKILL) || inf2&INF2_WEDDING_SKILL ) &&	// �މ�G??�W�`�F�b�N
		battle_check_target(sd,bl, BCT_ENEMY)<=0 ) {
		sd->canact_tick = tick;
		sd->canmove_tick = tick;
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}

	
	if(inf2 & (INF2_PARTY_ONLY|INF2_GUILD_ONLY) && sd->block_list::id != bl->id)
	{
		if( (inf2 & INF2_PARTY_ONLY && battle_check_target(sd,bl, BCT_PARTY) > 0) ||
			(inf2 & INF2_GUILD_ONLY && battle_check_target(sd,bl, BCT_GUILD) > 0) ||
			(sd->skillid == PF_SOULCHANGE && (maps[sd->block_list::m].flag.gvg || maps[sd->block_list::m].flag.pvp)) )//Soul Change overrides this restriction during pvp/gvg [Skotlex]
		{	// nothing
		}
		else
		{
			sd->skill_failed(sd->skillid);
			sd->canact_tick = tick;
			sd->canmove_tick = tick;
			sd->skillitem = sd->skillitemlv = 0xFFFF;
			return 0;
		}
	}

	range = skill_get_range(sd->skillid,sd->skilllv);
	if(range < 0)
		range = sd->get_range() - (range + 1);
	range += config.pc_skill_add_range;

	if ( sd->has_status(SC_COMBO) &&
		((sd->skillid == MO_EXTREMITYFIST && sd->get_statusvalue1(SC_COMBO).integer() == MO_COMBOFINISH) ||
		(sd->skillid == CH_TIGERFIST && sd->get_statusvalue1(SC_COMBO).integer() == MO_COMBOFINISH) ||
		(sd->skillid == CH_CHAINCRUSH && sd->get_statusvalue1(SC_COMBO).integer() == MO_COMBOFINISH) ||
		(sd->skillid == CH_CHAINCRUSH && sd->get_statusvalue1(SC_COMBO).integer() == CH_TIGERFIST) ||
		(sd->skillid == MO_EXTREMITYFIST && sd->get_statusvalue1(SC_COMBO).integer() == CH_TIGERFIST) ||
		(sd->skillid == MO_EXTREMITYFIST && sd->get_statusvalue1(SC_COMBO).integer() == CH_CHAINCRUSH)))
		range += skill_get_blewcount(MO_COMBOFINISH,sd->get_statusvalue2(SC_COMBO).integer());

	if(config.skill_out_range_consume) { // changed to allow casting when target walks out of range [Valaris]
		if(range < distance(*sd,*bl)) {
			sd->skill_failed(sd->skillid);
			sd->canact_tick = tick;
			sd->canmove_tick = tick;
			sd->skillitem = sd->skillitemlv = 0xFFFF;
			return 0;
		}
	}
	if(!skill_check_condition(sd,1)) {		// �g�p?���`�F�b�N
		sd->canact_tick = tick;
		sd->canmove_tick = tick;
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}


	if(config.pc_skill_log)
		ShowMessage("PC %d skill castend skill=%d\n",sd->block_list::id,sd->skillid);
	sd->stop_walking(0);



	switch( skill_get_nk(sd->skillid) )
	{
	case NK_NO_DAMAGE:
		if( (sd->skillid==AL_HEAL || (sd->skillid==ALL_RESURRECTION && *bl != BL_PC) || sd->skillid==PR_ASPERSIO) && bl->is_undead() )
			skill_castend_damage_id(sd,bl,sd->skillid,sd->skilllv,tick,0);
		else
			skill_castend_nodamage_id(sd,bl,sd->skillid,sd->skilllv,tick,0);
		break;
	case NK_SPLASH_DAMAGE:
	default:
		skill_castend_damage_id(sd,bl,sd->skillid,sd->skilllv,tick,0);
		break;
	}

	return 0;
}

/*==========================================
 * �X�L���g�p�i�r�������A�ꏊ�w��j
 *------------------------------------------
 */
int skill_castend_pos(int tid, unsigned long tick, int id, basics::numptr data)
{
	map_session_data* sd=map_session_data::from_blid(id);
	int range,maxcount;

	nullpo_retr(0, sd);

	if( !sd->is_on_map() )
		return 0;
	if( sd->skilltimer != tid )	// �^�C�}ID�̊m�F
		return 0;
	if(sd->skillid == 0xFFFF || sd->skilllv == 0xFFFF)	// skill has failed after starting casting
	{
		sd->skilltimer = -1;
		return 0;
	}
	if(sd->skillid != SA_CASTCANCEL && sd->skilltimer != -1 && (range = sd->skill_check(SA_FREECAST)) > 0) //Hope ya don't mind me borrowing range :X
		status_calc_speed(*sd, SA_FREECAST, range, 0); 

	sd->skilltimer=-1;
	if( sd->is_dead() )
	{
		sd->canact_tick = tick;
		sd->canmove_tick = tick;
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}

	if (!config.pc_skill_reiteration &&
			skill_get_unit_flag(sd->skillid)&UF_NOREITERATION &&
			skill_check_unit_range(sd->block_list::m,sd->skillx,sd->skilly,sd->skillid,sd->skilllv)) {
		sd->skill_failed(sd->skillid);
		sd->canact_tick = tick;
		sd->canmove_tick = tick;
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}

	if (config.pc_skill_nofootset &&
		(skill_get_unit_flag(sd->skillid) & UF_NOFOOTSET) &&
		skill_check_unit_range2(sd->block_list::m,sd->skillx,sd->skilly,sd->skillid,sd->skilllv,BL_PC) )
	{
		sd->skill_failed(sd->skillid);
		sd->canact_tick = tick;
		sd->canmove_tick = tick;
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}
	if(config.pc_land_skill_limit) {
		maxcount = skill_get_maxcount(sd->skillid);
		if(maxcount > 0) {
			int i,c;
			for(i=c=0;i<MAX_SKILLUNITGROUP;++i) {
				if(sd->skillunit[i].alive_count > 0 && sd->skillunit[i].skill_id == sd->skillid)
					++c;
			}
			if(c >= maxcount) {
				sd->skill_failed(sd->skillid);
				sd->canact_tick = tick;
				sd->canmove_tick = tick;
				sd->skillitem = sd->skillitemlv = 0xFFFF;
				return 0;
			}
		}
	}

	if(sd->skilllv <= 0) return 0;
	range = skill_get_range(sd->skillid,sd->skilllv);
	if(range < 0)
		range = sd->get_range() - (range + 1);
	range += config.pc_skill_add_range;

	if(config.skill_out_range_consume) {  // changed to allow casting when target walks out of range [Valaris]
		if(range < sd->get_distance(sd->skillx,sd->skilly))
		{
			sd->skill_failed(sd->skillid);
			sd->canact_tick = tick;
			sd->canmove_tick = tick;
			sd->skillitem = sd->skillitemlv = 0xFFFF;
			return 0;
		}
	}
	if(!skill_check_condition(sd,1)) {		// �g�p?���`�F�b�N
		sd->canact_tick = tick;
		sd->canmove_tick = tick;
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}

	if(config.pc_skill_log)
		ShowMessage("PC %d skill castend skill=%d\n",sd->block_list::id,sd->skillid);
	sd->stop_walking(0);

	skill_castend_pos2(sd,sd->skillx,sd->skilly,sd->skillid,sd->skilllv,tick,0);

	return 0;
}

/*==========================================
 * �X�L���g�p�i�r�������A�ꏊ�w���?�ۂ�?���j
 *------------------------------------------
 */
int skill_castend_pos2(block_list *src, int x,int y,unsigned short skillid,unsigned short skilllv,unsigned long tick,int flag)
{
	map_session_data *sd=NULL;
	int i,tmpx = 0,tmpy = 0, x1 = 0, y1 = 0;


	if(skillid > 0 && skilllv <= 0) return 0;	// celest

	nullpo_retr(0, src);

	if(*src==BL_PC){
		sd=(map_session_data *)src;
		nullpo_retr(0, sd);
		// can be also called from others then BL_PC
		// so check only here since we need a real map_session_data
		if(skill_not_ok(skillid, *sd)) // [MouseJstr]
			return 0;
	}

	if( skillid != WZ_METEOR &&
		skillid != AM_CANNIBALIZE &&
		skillid != AM_SPHEREMINE &&
		skillid != CR_CULTIVATION)
		clif_skill_poseffect(*src,skillid,skilllv,x,y,tick);

	switch(skillid)
	{
	case PR_BENEDICTIO:			// ��?�~��
		skill_area_temp[1] = src->id;

		maps[src->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag|BCT_ALL|1,skill_castend_nodamage_id),
			x, y, 1, BL_PC);

		maps[src->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag|BCT_ENEMY|1,skill_castend_damage_id),
			x, y, 1, BL_ALL);
		break;

	case BS_HAMMERFALL:			// �n���}?�t�H?��
		{
			int r = 2;
			if (skilllv > 5) {
				r = 14;
				skilllv = 5;	// �X�^�����オ�肷���邽�ߌv�Z��Lv5�ŌŒ�
			}
			skill_area_temp[1] = src->id;
			skill_area_temp[2] = x;
			skill_area_temp[3] = y;

			maps[src->m].foreachinarea(  CSkillArea(*src, skillid, skilllv, tick, flag|BCT_ENEMY|2,skill_castend_nodamage_id),
				x, y, r, BL_ALL);
		}
		break;

	case HT_DETECTING:				// �f�B�e�N�e�B���O
		{
			const int range=skilllv*2+1;
			if(src->x!=x)
				x+=(src->x-x>0)?-range:range;
			if(src->y!=y)
				y+=(src->y-y>0)?-range:range;

			maps[src->m].foreachinarea( CStatusChangetimer(*src,SC_SIGHT,tick),
				x, y, range, BL_ALL);
		}
		break;

	case MG_SAFETYWALL:			// �Z�C�t�e�B�E�H?��
	case MG_FIREWALL:			// �t�@�C��?�E�H?��
	case MG_THUNDERSTORM:		// �T���_?�X�g?��
	case AL_PNEUMA:				// �j��?�}
	case WZ_ICEWALL:			// �A�C�X�E�H?��
	case WZ_FIREPILLAR:			// �t�@�C�A�s��?
	case WZ_QUAGMIRE:			// �N�@�O�}�C�A
	case WZ_VERMILION:			// ��?�h�I�u���@?�~���I��
	case WZ_STORMGUST:			// �X�g?���K�X�g
	case WZ_HEAVENDRIVE:		// �w�����Y�h���C�u
	case PR_SANCTUARY:			// �T���N�`���A��
	case PR_MAGNUS:				// �}�O�k�X�G�N�\�V�Y��
	case CR_GRANDCROSS:			// �O�����h�N���X
	case NPC_GRANDDARKNESS:		// �ŃO�����h�N���X
	case HT_SKIDTRAP:			// �X�L�b�h�g���b�v
	case HT_LANDMINE:			// �����h�}�C��
	case HT_ANKLESNARE:			// �A���N���X�l�A
	case HT_SHOCKWAVE:			// �V���b�N�E�F?�u�g���b�v
	case HT_SANDMAN:			// �T���h�}��
	case HT_FLASHER:			// �t���b�V��?
	case HT_FREEZINGTRAP:		// �t��?�W���O�g���b�v
	case HT_BLASTMINE:			// �u���X�g�}�C��
	case HT_CLAYMORETRAP:		// �N���C���A?�g���b�v
	case AS_VENOMDUST:			// �x�m���_�X�g
	case AM_DEMONSTRATION:			// �f�����X�g��?�V����
	case PF_FOGWALL:			// �t�H�O�E�H?��
	case HT_TALKIEBOX:			// �g?�L?�{�b�N�X
	case PF_SPIDERWEB:			// �X�p�C�_?�E�F�b�u
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;

	case RG_GRAFFITI:			// Graffiti [Valaris]
		skill_clear_unitgroup(src);
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;

	case RG_CLEANER: // [Valaris]

		maps[src->m].foreachinarea( CSkillGraffitiRemover(),
			x,y,5,BL_SKILL);
		break;
	case SA_VOLCANO:		// �{���P?�m
	case SA_DELUGE:			// �f����?�W
	case SA_VIOLENTGALE:	// �o�C�I�����g�Q�C��
	case SA_LANDPROTECTOR:	// �����h�v���e�N�^?
		skill_clear_element_field(src);//?�Ɏ�����?�����Ă���?������N���A
		skill_unitsetting(src,skillid,skilllv,x,y,0);
		break;

	case WZ_METEOR:				//���e�I�X�g?��
		{
			int myflag=0;
			for(i=0;i<2+(skilllv>>1);++i) {
				int j=0;
				do {
					tmpx = x + (rand()%7 - 3);
					tmpy = y + (rand()%7 - 3);
					if(tmpx < 0)
						tmpx = 0;
					else if(tmpx >= maps[src->m].xs)
						tmpx = maps[src->m].xs - 1;
					if(tmpy < 0)
						tmpy = 0;
					else if(tmpy >= maps[src->m].ys)
						tmpy = maps[src->m].ys - 1;
					++j;
				} while( !maps[src->m].is_passable(tmpx,tmpy) && j<100 );
				if(j >= 100)
					continue;
				if(myflag==0){
					clif_skill_poseffect(*src,skillid,skilllv,tmpx,tmpy,tick);
					myflag=1;
				}
				if(i > 0)
					skill_addtimerskill(src,tick+i*1000,0,tmpx,tmpy,skillid,skilllv,(x1<<16)|y1,flag);
				x1 = tmpx;
				y1 = tmpy;
			}
			skill_addtimerskill(src,tick+i*1000,0,tmpx,tmpy,skillid,skilllv,-1,myflag);
		}
		break;

	case AL_WARP:				// ��?�v�|?�^��
		if(sd) {
			if(maps[sd->block_list::m].flag.nowarp)	// �e���|�֎~
				break;
			clif_skill_warppoint(*sd,sd->skillid,sd->status.save_point.mapname,
				(sd->skilllv>1)?sd->status.memo_point[0].mapname:"",
				(sd->skilllv>2)?sd->status.memo_point[1].mapname:"",
				(sd->skilllv>3)?sd->status.memo_point[2].mapname:"");
		}
		break;

	case MO_BODYRELOCATION:
		if (sd)
		{
			sd->movepos(x,y);
			pc_blockskill_start(*sd, MO_EXTREMITYFIST, 2000);
		}
		else if (*src == BL_MOB)
		{
			struct mob_data *md = (struct mob_data *)src;
			mob_warp(*md, -1, x, y, 0);
			clif_spawnmob(*md);
		}
		break;
	case TK_HIGHJUMP:
		clif_skill_nodamage(*src,*src,skillid,skilllv,0);
		if (sd) pc_setpos(*sd,sd->mapname,x,y,0);
		//TODO: Add mob implementation for this skill. [Skotlex]
		break;    
	case AM_CANNIBALIZE:	// �o�C�I�v�����g
		if(sd) {
			int id;
			int summons[5] = { 1020, 1068, 1118, 1500, 1368 };
			struct mob_data *md;

			// Correct info, don't change any of this! [celest]
			id = mob_once_spawn (sd, "this", x, y, sd->status.name, summons[skilllv-1] ,1,"");

			if( (md= mob_data::from_blid(id)) !=NULL )
			{
				md->master_id = sd->block_list::id;
				// different levels of HP according to skill level
				md->hp = 1500 + skilllv * 200 + sd->status.base_level * 10;
				md->state.special_mob_ai = 1;
				//��ړ��ŃA�N�e�B�u�Ŕ�������[0x0:��ړ� 0x1:�ړ� 0x4:ACT 0x8:��ACT 0x40:������ 0x80:�����L]
				md->mode = 0x0 + 0x4 + 0x80;
				md->deletetimer = add_timer (gettick() + skill_get_time(skillid,skilllv), mob_timer_delete, id, 0);
			}
			// To-do: ���҂���郂���X�^�[�ɂ͏��҂����v���[���[�̖��O���t���܂�
			// (attach name of player?)
			clif_skill_poseffect(*src,skillid,skilllv,x,y,tick);
		}
		break;
	case AM_SPHEREMINE:	// �X�t�B�A?�}�C��
		if(sd){
			int id = mob_once_spawn(sd, "this", x, y, sd->status.name, 1142, 1, "");
			struct mob_data *md = mob_data::from_blid(id);
			if( md!=NULL )
			{
				md->master_id = sd->block_list::id;
				md->max_hp=md->hp = 2000 + skilllv * 400;
				md->state.special_mob_ai = 2;
				md->deletetimer = add_timer (gettick() + skill_get_time(skillid,skilllv), mob_timer_delete, id, 0);
			}
			clif_skill_poseffect(*src,skillid,skilllv,x,y,tick);
		}
		break;

	// Slim Pitcher [Celest]
	case CR_SLIMPITCHER:
		{
			if (sd)
			{
				i = skilllv%11 - 1;
				int j = pc_search_inventory(*sd,skill_db[skillid].itemid[i]);
				if( j < 0 || skill_db[skillid].itemid[i] <= 0 || 
					sd->inventory_data[j] == NULL ||
					sd->status.inventory[j].amount < skill_db[skillid].amount[i] ||
					sd->inventory_data[j]->use_script == NULL || sd->inventory_data[j]->use_script->script==NULL )
				{
					sd->skill_failed(skillid);
					return 1;
				}
				sd->state.potion_flag = 1;
				sd->potion_hp = 0;
				CScriptEngine::run(sd->inventory_data[j]->use_script->script,0,sd->block_list::id,0);
				pc_delitem(*sd,j,skill_db[skillid].amount[i],0);
				sd->state.potion_flag = 0;
				clif_skill_poseffect(*src,skillid,skilllv,x,y,tick);
				if(sd->potion_hp > 0) {

					maps[src->m].foreachinarea(  CSkillArea(*src,skillid,skilllv,tick,flag|BCT_PARTY|BCT_GUILD|1,skill_castend_nodamage_id),
						x,y,3,BL_ALL);
				}
			}
		}
		break;

	case HW_GANBANTEIN:
		if (rand()%100 < 80) {
			clif_skill_poseffect(*src,skillid,skilllv,x,y,tick);
			maps[src->m].foreachinarea( CSkillGanbatein(),
				x, y, 1, BL_SKILL);
		} else {
			sd->skill_failed(skillid);
			return 1;
		}
		break;
	
	case HW_GRAVITATION:
	{
		struct skill_unit_group *sg;
		clif_skill_poseffect(*src,skillid,skilllv,x,y,tick);
		sg = skill_unitsetting(src,skillid,skilllv,x,y,0);	
		status_change_start(src,(status_t)SkillStatusChangeTable[skillid],skilllv,0,BCT_SELF,basics::numptr(sg),
			skill_get_time(skillid,skilllv),0);
		break;
	}
	// Plant Cultivation [Celest]
	case CR_CULTIVATION:
		{
			if (sd) {
				i = skilllv - 1;
				int j = pc_search_inventory(*sd,skill_db[skillid].itemid[i]);
				if(j < 0 || skill_db[skillid].itemid[i] <= 0 || sd->inventory_data[j] == NULL ||
					sd->status.inventory[j].amount < skill_db[skillid].amount[i]) {
					sd->skill_failed(skillid);
					return 1;
				}
				pc_delitem(*sd,j,skill_db[skillid].amount[i],0);
				if (rand()%100 > 50) {
					sd->skill_failed(skillid);
					return 1;
				}
				mob_once_spawn(sd, "this", x, y, "--ja--",
					(skilllv < 2 ? 1084 + rand() % 2 : 1078 + rand() % 6 ), 1, "");
				clif_skill_poseffect(*src,skillid,skilllv,x,y,tick);
			}
		}
		break;
	}

	return 0;
}

/*==========================================
 * �X�L���g�p�i�r�������Amap�w��j
 *------------------------------------------
 */
int skill_castend_map( map_session_data *sd,int skill_num, const char *mapname)
{
	int x=0,y=0;

	nullpo_retr(0, sd);
	if( !sd->is_on_map() || sd->is_dead() )
		return 0;

	if(skill_not_ok(skill_num, *sd))
		return 0;

	if( sd->opt1>0 || sd->status.option&2 )
		return 0;
	//�X�L�����g���Ȃ�?�Ԉُ풆
	{
		if( sd->has_status(SC_DIVINA) ||
			sd->has_status(SC_ROKISWEIL) ||
			sd->has_status(SC_AUTOCOUNTER) ||
			sd->has_status(SC_STEELBODY) ||
			sd->has_status(SC_DANCING) ||
			sd->has_status(SC_BERSERK) ||
			sd->has_status(SC_MARIONETTE) )
			return 0;
	}

	if( skill_num != sd->skillid)	// �s���p�P�b�g�炵��
		return 0;

	//Clear it up to prevent resent packets through! [Skotlex]
	basics::TScopeChange<unsigned short> clear(sd->skillid, 0);

	sd->stop_attack();

	if(config.pc_skill_log)
		ShowMessage("PC %d skill castend skill =%d map=%s\n",sd->block_list::id,skill_num,mapname);
	sd->stop_walking(0);

	if(strcmp(mapname,"cancel")==0)
		return 0;

	switch(skill_num){
	case AL_TELEPORT:		// �e���|?�g
		if(strcmp(mapname,"Random")==0)
			pc_randomwarp(*sd,3);
		else
			pc_setpos(*sd,sd->status.save_point.mapname,
				sd->status.save_point.x,sd->status.save_point.y,3);
		break;

	case AL_WARP:			// ��?�v�|?�^��
		{
			const struct point *p[4];
			struct skill_unit_group *group;
			int i;
			int maxcount=0;
			unsigned int tick=gettick();
			p[0] = &sd->status.save_point;
			p[1] = &sd->status.memo_point[0];
			p[2] = &sd->status.memo_point[1];
			p[3] = &sd->status.memo_point[2];

			if((maxcount = skill_get_maxcount(sd->skillid)) > 0) {
				int c;
				for(i=c=0;i<MAX_SKILLUNITGROUP;++i) {
					if(sd->skillunit[i].alive_count > 0 && sd->skillunit[i].skill_id == sd->skillid)
						++c;
				}
				if(c >= maxcount) {
					sd->skill_failed(sd->skillid);
					sd->canact_tick = gettick();
					sd->canmove_tick = gettick();
					sd->skillitem = sd->skillitemlv = 0xFFFF;
					return 0;
				}
			}

			if(sd->skilllv <= 0)
				return 0;
			for(i=0; i<sd->skilllv && i<4; ++i)
			{
				if(strcmp(mapname,p[i]->mapname)==0)
				{
					x=p[i]->x;
					y=p[i]->y;
					break;
				}
			}
			if(x==0 || y==0)	// �s���p�P�b�g�H
				return 0;

			if(!skill_check_condition(sd,3))
				return 0;

			if(skill_check_unit_range2(sd->block_list::m,sd->skillx,sd->skilly,sd->skillid,sd->skilllv,BL_PC) > 0) {
				sd->skill_failed(0);
				sd->canact_tick = tick;
				sd->canmove_tick = tick;
				sd->skillitem = sd->skillitemlv = 0xFFFF;
				return 0;
			}
			if((group=skill_unitsetting(sd,sd->skillid,sd->skilllv,sd->skillx,sd->skilly,0))==NULL)
				return 0;
			group->valstring = mapname;
			group->val2=(x<<16)|y;
		}
		break;
	}

	return 0;
}

/*==========================================
 * �X�L�����j�b�g�ݒ�?��
 *------------------------------------------
 */
struct skill_unit_group *skill_unitsetting(block_list *src, unsigned short skillid,unsigned short skilllv,int x,int y,int flag)
{
	struct skill_unit_group *group;
	int i,limit,val1=0,val2=0,val3=0;
	int count=0;
	int target,interval,range,unit_flag;
	struct skill_unit_layout *layout;
	int active_flag=1;

	nullpo_retr(0, src);

	limit = skill_get_time(skillid,skilllv);
	range = skill_get_unit_range(skillid);
	interval = skill_get_unit_interval(skillid);
	target = skill_get_unit_target(skillid);
	unit_flag = skill_get_unit_flag(skillid);
	layout = skill_get_unit_layout(skillid,skilllv,src,x,y);

	if (unit_flag&UF_DEFNOTENEMY && config.defnotenemy)
		target = BCT_NOENEMY;

	switch(skillid){	// �ݒ�

	case MG_SAFETYWALL:			// �Z�C�t�e�B�E�H?��
		val2=skilllv+1;
		break;
	case MG_FIREWALL:			// �t�@�C��?�E�H?��
		if( src->has_status(SC_VIOLENTGALE) )
			limit = limit*3/2;
		val2=4+skilllv;
		break;

	case AL_WARP:				// ��?�v�|?�^��
		val1=skilllv+6;
		if(flag==0)
			limit=2000;
		active_flag=0;
		break;

	case PR_SANCTUARY:			// �T���N�`���A��
		val1=(skilllv+3)*2;
		val2=(skilllv>6)?777:skilllv*100;
		interval += 500;
		break;

	case WZ_FIREPILLAR:			// �t�@�C�A?�s��?
		if(flag!=0)
			limit=1000;
		val1=skilllv+2;
		if(skilllv >= 6)
			range=2;
		break;
	case WZ_METEOR:
		if (skilllv > 10)			//�L�͈̓��e�I
			range = 10;
		break;
	case WZ_VERMILION:
		if (skilllv > 10)			//�L�͈�LOV
			range = 25;
		break;

	case HT_SANDMAN:			// �T���h�}��
	case HT_CLAYMORETRAP:		// �N���C���A?�g���b�v
	case HT_SKIDTRAP:			// �X�L�b�h�g���b�v
	case HT_LANDMINE:			// �����h�}�C��
	case HT_ANKLESNARE:			// �A���N���X�l�A
	case HT_FLASHER:			// �t���b�V��?
	case HT_FREEZINGTRAP:		// �t��?�W���O�g���b�v
	case HT_BLASTMINE:			// �u���X�g�}�C��
		if (maps[src->m].flag.gvg)
		{
			limit *= 4;			// longer trap times in WOE [celest]
			//target = BCT_ALL;	//Hits everyone in WOE [Skotlex]
		}
		break;
	case HT_SHOCKWAVE:			// �V���b�N�E�F?�u�g���b�v
		if (maps[src->m].flag.gvg) limit *= 4;
		val1=skilllv*15+10;
		break;

	case SA_LANDPROTECTOR:	// �O�����h�N���X
		{
			int aoe_diameter;	// -- aoe_diameter (moonsoul) added for sage Area Of Effect skills
			val1=skilllv*15+10;
			aoe_diameter=skilllv+skilllv%2+5;
			count=aoe_diameter*aoe_diameter;	// -- this will not function if changed to ^2 (moonsoul)
		}
		break;

	case BA_WHISTLE:			// ���J
		if(*src == BL_PC)
			val1 = (src->skill_check(BA_MUSICALLESSON)+1)>>1;
		val2 = ((src->get_agi()/10)&0xffff)<<16;
		val2 |= (src->get_luk()/10)&0xffff;
		break;
	case DC_HUMMING:			// �n�~���O
		if(*src == BL_PC)
			val1 = (src->skill_check(DC_DANCINGLESSON)+1)>>1;
		val2 = src->get_dex()/10;
		break;
	case DC_DONTFORGETME:		// ����Y��Ȃ��Łc
		if(*src == BL_PC)
			val1 = (src->skill_check(DC_DANCINGLESSON)+1)>>1;
		//val2 = ((src->get_str()/20)&0xffff)<<16;
		val2 = ((src->get_dex()/20)&0xffff)<<16;
		val2 |= (src->get_agi()/10)&0xffff;
		break;
	case BA_POEMBRAGI:			// �u���M�̎�
		if(*src == BL_PC)
			val1 = src->skill_check(BA_MUSICALLESSON);
		val2 = ((src->get_dex()/10)&0xffff)<<16;
		val2 |= (src->get_int()/5)&0xffff;
		break;
	case BA_APPLEIDUN:			// �C�h�D���̗ь�
		if(*src == BL_PC)
			val1 = src->skill_check(BA_MUSICALLESSON)&0xffff;
		val2 |= (src->get_vit())&0xffff; // Used modulus to prevent e.g. 42VIT/10*5 gives 21 HP healing bonus instead if 20 [DracoRPG]
		val3 = 0;//�񕜗p�^�C���J�E���^(6�b?��1?��)
		break;
	case DC_SERVICEFORYOU:		// �T?�r�X�t�H?��?
		if(*src == BL_PC)
			val1 = (src->skill_check(DC_DANCINGLESSON)+1)>>1;
		val2 = src->get_int()/10;
		break;
	case BA_ASSASSINCROSS:		// �[�z�̃A�T�V���N���X
		if(*src == BL_PC)
			val1 = (src->skill_check(BA_MUSICALLESSON)+1)>>1;
		val2 = src->get_agi()/20;
		break;
	case DC_FORTUNEKISS:		// �K�^�̃L�X
		if(*src == BL_PC)
			val1 = (src->skill_check(DC_DANCINGLESSON)+1)>>1;
		val2 = src->get_luk()/10;
		break;

	case PF_FOGWALL:	// �t�H�O�E�H?��
		if( src->has_status(SC_DELUGE) )
			limit *= 2;
		break;

	case RG_GRAFFITI:			// Graffiti
		count=1;	// Leave this at 1 [Valaris]
		break;
//	default:
//		//if(config.error_log)
//			ShowMessage ("skill_unitsetting: Unknown skill id = %d\n",skillid);
//		return 0;
	}

	group=skill_initunitgroup(src,(count > 0 ? count : layout->count),
		skillid,skilllv,skill_get_unit_id(skillid,flag&1));
	nullpo_retr(NULL, group);
	group->limit=limit;
	group->val1=val1;
	group->val2=val2;
	group->val3=val3;
	group->target_flag=target;
	group->interval=interval;
	if( skillid==HT_TALKIEBOX || skillid==RG_GRAFFITI )
	{
		group->valstring = talkie_mes;
	}
	for(i=0;i<layout->count;++i)
	{
		struct skill_unit *unit;
		int ux,uy,myval1=skilllv,myval2=0,alive=1;
		limit=group->limit;
		ux = x + layout->dx[i];
		uy = y + layout->dy[i];
		switch (skillid)
		{
		case MG_FIREWALL:		// ?t?@?C????E?H???
			myval2=group->val2;
			break;
		case WZ_ICEWALL:		// ?A?C?X?E?H???
			if(skilllv <= 1)
				myval1 = 500;
			else
				myval1 = 200 + 200*skilllv;
			break;
		case RG_GRAFFITI:	// Graffiti [Valaris]
			ux+=(i%5-2);
			uy+=(i/5-2);
			break;
		}
		if(range<=0)
		{
			maps[src->m].foreachincell(CSkillLandprotector(skillid,alive),ux,uy,BL_SKILL);
		}

		if(skillid==WZ_ICEWALL && alive)
		{

			if( (src->x == x && src->y==y) || !maps[src->m].is_passable(ux,uy) )
				alive=0;
			else
			{
				myval2=maps[src->m].get_type(ux,uy);
				maps[src->m].set_icewall(ux,uy);
				clif_changemapcell(src->m,ux,uy,mapcell_t::GAT_GROUND,0);
			}
		}
		if( alive && maps[src->m].is_wall(ux,uy) )
			alive = 0;

		if(alive)
		{
			nullpo_retr(NULL, unit=skill_initunit(group,i,ux,uy));
			unit->val1=myval1;
			unit->val2=myval2;
			unit->limit=limit;
			unit->range=range;

			if (range==0 && active_flag)
			{
				maps[unit->block_list::m].foreachincell( CSkillUnitEffect(*unit,gettick(),1),
					unit->block_list::x,unit->block_list::y,BL_ALL);
			}
		}
	}
	
	return group;
}

/*==========================================
 * �X�L�����j�b�g��?���C�x���g
 *------------------------------------------
 */
int skill_unit_onplace(struct skill_unit *src,block_list *bl,unsigned long tick)
{
	struct skill_unit_group *sg;
	block_list *ss;
	struct skill_unit *unit2;
	status_t type;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);
	
	if( !bl->is_on_map() || !src->alive || bl->is_dead() )
		return 0;

	sg = src->group;
	nullpo_retr(0, sg);
	ss = block_list::from_blid(sg->src_id);
	nullpo_retr(0, ss);
	
	type = (status_t)SkillStatusChangeTable[sg->skill_id];

	if (battle_check_target(src,bl,sg->target_flag)<=0)
		return 0;

	// �Ώۂ�LP��ɋ���ꍇ�͖���
	if (block_list::skillunit_oncell(*bl,bl->x,bl->y,SA_LANDPROTECTOR,NULL))
		return 0;

	switch (sg->unit_id) {
	case UNT_PNEUMA:	// �j���[�}
	case UNT_SAFETYWALL:	// �Z�C�t�e�B�E�H�[��
		if( !bl->has_status((status_t)type) )
			status_change_start(bl,type,sg->skill_lv,basics::numptr(src),0,0,sg->limit,0);
		break;

	case UNT_WARP:	// ���[�v�|�[�^��(������)
		if(*bl==BL_PC)
		{
			map_session_data *sd = bl->get_sd();
			if(sd && src->block_list::m == bl->m && src->block_list::x == bl->x && src->block_list::y == bl->y &&
				src->block_list::x == sd->walktarget.x && src->block_list::y == sd->walktarget.y) {
				if( config.chat_warpportal || !sd->chat )
				{
					pc_setpos(*sd,sg->valstring,sg->val2>>16,sg->val2&0xffff,3);
					if( sg->src_id == bl->id || (sg->valstring == maps[src->block_list::m].mapname &&
						src->block_list::x == (sg->val2>>16) && src->block_list::y == (sg->val2&0xffff)) )
						skill_delunitgroup(*sg);
					if (--sg->val1<=0)
						skill_delunitgroup(*sg);
				}
			}
		} else if(*bl==BL_MOB && config.mob_warpportal){
			int m = maps.index_of(sg->valstring);
			mob_warp(*((struct mob_data *)bl),m,sg->val2>>16,sg->val2&0xffff,3);
		}
		break;

	case UNT_QUAGMIRE:	// �N�@�O�}�C�A
		if(status_isimmune(bl))
			break;
		if( !bl->has_status((status_t)type) )
			status_change_start(bl,type,sg->skill_lv,basics::numptr(src),0,0,
				skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;

	case UNT_VOLCANO:	// �{���P?�m
	case UNT_DELUGE:	// �f����?�W
	case UNT_VIOLENTGALE:	// �o�C�I�����g�Q�C��
		if ( bl->has_status((status_t)type) )
		{
			unit2 = (struct skill_unit *)bl->get_statusvalue4((status_t)type).pointer();
			if (unit2 && unit2->group &&
				(unit2==src || DIFF_TICK(sg->tick,unit2->group->tick)<=0))
				break;
		}
		status_change_start(bl,type,sg->skill_lv,basics::numptr(src),0,0,
			skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;

	case UNT_LULLABY:	// �q��S
	case UNT_RICHMANKIM:	// �j�����h�̉�
	case UNT_ETERNALCHAOS:	// �i���̍���
	case UNT_DRUMBATTLEFIELD:	// ?���ۂ̋���
	case UNT_RINGNIBELUNGEN:	// �j?�x�����O�̎w��
	case UNT_ROKISWEIL:	// ���L�̋���
	case UNT_INTOABYSS:	// �[���̒���
	case UNT_SIEGFRIED:	// �s���g�̃W?�N�t��?�h
	case UNT_DISSONANCE:	// �s���a��
	case UNT_WHISTLE:	// ���J
	case UNT_ASSASSINCROSS:	// �[�z�̃A�T�V���N���X
	case UNT_POEMBRAGI:	// �u���M�̎�
	case UNT_APPLEIDUN:	// �C�h�D���̗ь�
	case UNT_UGLYDANCE:	// ��������ȃ_���X
	case UNT_HUMMING:	// �n�~���O
	case UNT_DONTFORGETME:	// ����Y��Ȃ��Łc
	case UNT_FORTUNEKISS:	// �K�^�̃L�X
	case UNT_SERVICEFORYOU:	// �T?�r�X�t�H?��?
	case UNT_HERMODE:	// Wand of Hermod
		if (sg->src_id==bl->id)
			break;
		if ( bl->has_status(type) )
		{
			unit2 = (struct skill_unit *)bl->get_statusvalue4((status_t)type).pointer();
			if (unit2 && unit2->group &&
				(unit2 == src || DIFF_TICK(sg->tick,unit2->group->tick)<=0))
				break;
		}
		status_change_start(bl,type,sg->skill_lv,sg->val1,sg->val2,
				basics::numptr(src),skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;

	case UNT_BASILICA:	// Basilica
		if (battle_check_target(src,bl,BCT_NOENEMY)>0) {
			if( bl->has_status(type) )
			{
				struct skill_unit_group *sg2 = (struct skill_unit_group *)bl->get_statusvalue4(type).pointer();
				if (sg2 && (sg2 == src->group || DIFF_TICK(sg->tick,sg2->tick)<=0))
					break;
			}
			status_change_start(bl,type,sg->skill_lv,0,0,basics::numptr(sg),
				skill_get_time2(sg->skill_id,sg->skill_lv),0);
		} else if(0 != (0x20&bl->get_mode()))
			skill_blown(src,bl,1);
		break;

	case UNT_FOGWALL:	// �t�H�O�E�H?��
		if ( bl->has_status(type) )
		{
			struct skill_unit_group *sg2 = (struct skill_unit_group *)bl->get_statusvalue4(type).pointer();
			if (sg2 && (sg2 == src->group || DIFF_TICK(sg->tick,sg2->tick)<=0))
				break;
		}
		status_change_start (bl, type, sg->skill_lv, sg->val1, sg->val2, basics::numptr(sg),
				skill_get_time2(sg->skill_id, sg->skill_lv), 0);
		if (battle_check_target(src,bl,BCT_ENEMY)>0)
			skill_additional_effect (ss, bl, sg->skill_id, sg->skill_lv, BF_MISC, tick);
		break;

	case UNT_GRAVITATION:	// Gravitation
		if (battle_check_target(src,bl,BCT_ENEMY)>0) {
			if (bl->has_status(type))
			{
				struct skill_unit_group *sg2 = (struct skill_unit_group *)bl->get_statusvalue4(type).pointer();
				if (sg2 && (sg2 == src->group || DIFF_TICK(sg->tick,sg2->tick)<=0))
					break;
				if( 0==(bl->get_mode()&0x20) )
					break;
			}
			status_change_start(bl,type,sg->skill_lv,5*sg->skill_lv,BCT_ENEMY,basics::numptr(sg),
				skill_get_time2(sg->skill_id,sg->skill_lv),0);
		}
		break;

	case UNT_CALLPARTNER:				// ���Ȃ���_?�������ł�
	case UNT_GOSPEL:				// �S�X�y��
	//�Ƃ肠�����������Ȃ�
		break;
	/*	default:
		if(config.error_log)
			ShowMessage("skill_unit_onplace: Unknown skill unit id=%d block=%d\n",sg->unit_id,bl->id);
		break;*/
	
	case UNT_ICEWALL: //Bah, destroy the cell. [Skotlex]
	//	skill_blown(&src->bl,bl,1,2); //I prefer knockback, have to figure out how to make it work...
		src->val1 = 0;
		if(src->limit + sg->tick > tick + 700)
			src->limit = DIFF_TICK(tick+700,sg->tick);
		break;
	}

	return 0;
}

/*==========================================
 * �X�L�����j�b�g�̔����C�x���g(�^�C�}�[����)
 *------------------------------------------
 */
int skill_unit_onplace_timer(struct skill_unit *src,block_list *bl,unsigned long tick)
{
	struct skill_unit_group *sg;
	block_list *ss;
	int splash_count=0;
	struct skill_unit_group_tickset *ts;
	status_t type;
	int diff=0;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);

	if (*bl!=BL_PC && *bl!=BL_MOB)
		return 0;
	
	if( !bl->is_on_map() || !src->alive ||
			(*bl==BL_PC && ((map_session_data *)bl)->is_dead()) )
		return 0;

	nullpo_retr(0, sg=src->group);
	nullpo_retr(0, ss=block_list::from_blid(sg->src_id));

	type = (status_t)SkillStatusChangeTable[sg->skill_id];

	// �Ώۂ�LP��ɋ���ꍇ�͖���
	if (block_list::skillunit_oncell(*bl,bl->x,bl->y,SA_LANDPROTECTOR,NULL))
		return 0;

	// �O�ɉe�����󂯂Ă���interval�̊Ԃ͉e�����󂯂Ȃ�
	nullpo_retr(0,ts = skill_unitgrouptickset_search(bl,sg,tick));
	diff = DIFF_TICK(tick,ts->tick);
	if (sg->skill_id == PR_SANCTUARY)
		diff += 500; // �V�K�ɉ񕜂������j�b�g�����J�E���g���邽�߂̎d�|��
	if (diff < 0)
		return 0;
	ts->tick = tick+sg->interval;
	// GX�͏d�Ȃ��Ă�����3HIT���Ȃ�
	if( (sg->skill_id==CR_GRANDCROSS ||sg->skill_id==NPC_GRANDDARKNESS)&& !config.gx_allhit)
	{
		const int cnt = maps[bl->m].countoncell(bl->x,bl->y,BL_ALL);
		ts->tick += sg->interval*(cnt-1);
	}

	switch (sg->unit_id) {
	case UNT_SANCTUARY:	// �T���N�`���A��
		{
			int race = bl->get_race();

			if ( bl->is_undead() || race==6) {
				if (skill_attack(BF_MAGIC, ss, src, bl, sg->skill_id, sg->skill_lv, tick, 0)) {
					// reduce healing count if this was meant for damaging [hekate]
					sg->val1 -= 2;
					//sg->val1--;	// �`���b�g�L�����Z���ɑΉ�
				}
			} else {
				int heal = sg->val2;
				if( bl->get_hp() >= bl->get_max_hp() )
					break;
				if (status_isimmune(bl))
					heal = 0;	// ����峃J�[�h�i�q�[���ʂO�j
				clif_skill_nodamage(*src, *bl, AL_HEAL, heal, 1);
				battle_heal(NULL, bl, heal, 0, 0);
				if (diff >= 500)
					sg->val1--;	// �V�K�ɓ��������j�b�g�����J�E���g
			}
			if (sg->val1 <= 0)
				skill_delunitgroup(*sg);
			break;
		}

	case UNT_MAGNUS:	// �}�O�k�X�G�N�\�V�Y��
		{
			int race = bl->get_race();
			if (!bl->is_undead() && race!=6)
				return 0;
			skill_attack(BF_MAGIC,ss,src,bl,sg->skill_id,sg->skill_lv,tick,0);
			++(src->val2);
			break;
		}

	case UNT_FIREWALL:	// �t�@�C���[�E�H�[��
		skill_attack(BF_MAGIC,ss,src,bl,sg->skill_id,sg->skill_lv,tick,0);
		if (--src->val2<=0)
			skill_delunit(src);
		break;
	case UNT_MAGIC_SKILLS:	// ���[�h�I�u���@�[�~���I��(TS,MS,FN,SG,HD,GX,��GX)
		skill_attack(BF_MAGIC,ss,src,bl,sg->skill_id,sg->skill_lv,tick,0);
		break;
	case UNT_FIREPILLAR_HIDDEN:	// �t�@�C�A�[�s���[(�����O)
		skill_delunit(src);
		skill_unitsetting(ss,sg->skill_id,sg->skill_lv,src->block_list::x,src->block_list::y,1);
		break;

	case UNT_FIREPILLAR_ACTIVE:	// �t�@�C�A�[�s���[(������)
		maps[bl->m].foreachinarea( CSkillAttackArea(BF_MAGIC,*ss,*src,sg->skill_id,sg->skill_lv,tick,0,BCT_ENEMY),
			bl->x,bl->y,1,BL_ALL);
		break;

	case UNT_SKIDTRAP:	// �X�L�b�h�g���b�v
		{
			int i,c = skill_get_blewcount(sg->skill_id,sg->skill_lv);
			if(maps[bl->m].flag.gvg) c = 0;
			for(i=0;i<c;++i)
				skill_blown(src,bl,1|0x30000);
			sg->unit_id = UNT_USEDTRAP;
			clif_changelook(*src,LOOK_BASE,sg->unit_id);
			sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		}
		break;	

	case UNT_LANDMINE:	// �����h�}�C��
		skill_attack(BF_MISC,ss,src,bl,sg->skill_id,sg->skill_lv,tick,0);
		sg->unit_id = UNT_USEDTRAP;
		clif_changelook(*src,LOOK_BASE, UNT_FIREPILLAR_ACTIVE);
		sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		break;

	case UNT_BLASTMINE:	// �u���X�g�}�C��
	case UNT_SHOCKWAVE:	// �V���b�N�E�F?�u�g���b�v
	case UNT_SANDMAN:	// �T���h�}��
	case UNT_FLASHER:	// �t���b�V��?
	case UNT_FREEZINGTRAP:	// �t��?�W���O�g���b�v
	case UNT_CLAYMORETRAP:	// �N���C���A?�g���b�v

		splash_count = maps[src->block_list::m].foreachinarea( CSkillCounttarget(*src),
			src->block_list::x, src->block_list::y, src->range, BL_ALL);

		maps[src->block_list::m].foreachinarea( CSkillTrapsplash(*src,tick,splash_count),			
			src->block_list::x, src->block_list::y, src->range, BL_ALL);

		sg->unit_id = UNT_USEDTRAP;
		clif_changelook(*src,LOOK_BASE,sg->unit_id);
		sg->limit=DIFF_TICK(tick,sg->tick)+1500;
		break;

	case UNT_ANKLESNARE:	// �A���N���X�l�A
		if(sg->val2==0 && !bl->has_status(SC_ANKLE))
		{
			int moveblock = ( bl->x/BLOCK_SIZE != src->block_list::x/BLOCK_SIZE || bl->y/BLOCK_SIZE != src->block_list::y/BLOCK_SIZE);
			int sec = skill_get_time2(sg->skill_id,sg->skill_lv) - bl->get_agi()*100;
			if(bl->get_mode()&0x20)
				sec = sec/5;
			if (sec < 3000+30*sg->skill_lv)	// minimum time of 3 seconds [celest]
				sec = 3000+30*sg->skill_lv;
			bl->stop_walking(1);
			status_change_start(bl,SC_ANKLE,sg->skill_lv,0,0,0,sec,0);

			skill_unit_move(*bl,tick,0);
			if(moveblock) bl->delblock();
			bl->x = src->block_list::x;
			bl->y = src->block_list::y;
			if(moveblock) bl->addblock();
			skill_unit_move(*bl,tick,1);
			clif_fixobject(*bl);
			clif_01ac(*src);
			sg->limit=DIFF_TICK(tick,sg->tick) + sec;
			sg->val2=bl->id;
			sg->interval = -1;
			src->range = 0;
		}
		break;

	case UNT_VENOMDUST:	// �x�m���_�X�g
		if( !bl->has_status(type) )
			status_change_start(bl,type,sg->skill_lv,basics::numptr(src),0,0,skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;

	case UNT_LULLABY:
		if (ss->id == bl->id)
			break;
		skill_additional_effect(ss, bl, sg->skill_id, sg->skill_lv, BF_LONG|BF_SKILL|BF_MISC, tick);
		break;

	case UNT_DISSONANCE:
		skill_attack(BF_MISC, ss, src, bl, sg->skill_id, sg->skill_lv, tick, 0);
		break;

	case UNT_DEMONSTRATION:	// �f�����X�g��?�V���� 
		skill_attack(BF_WEAPON, ss, src, bl, sg->skill_id, sg->skill_lv, tick, 0);
		break;

	case UNT_TALKIEBOX:				// �g�[�L�[�{�b�N�X
		if (sg->src_id == bl->id) //����������ł��������Ȃ�
			break;
		if (sg->val2 == 0){
			clif_talkiebox(*src, sg->valstring);
			sg->unit_id = UNT_USEDTRAP;
			clif_changelook(*src, LOOK_BASE, sg->unit_id);
			sg->limit = DIFF_TICK(tick, sg->tick) + 5000;
			sg->val2 = -1; //����
		}
		break;	

	// Basilica
	case UNT_BASILICA:				// �o�W���J
	   	if (battle_check_target(src,bl,BCT_ENEMY)>0 &&
			!(bl->get_mode()&0x20))
			skill_blown(src,bl,1);
		if (sg->src_id==bl->id)
			break;
		if (battle_check_target(src,bl,BCT_NOENEMY)>0 && !bl->has_status(type))
			status_change_start(bl,type,sg->skill_lv,basics::numptr(src),0,0,
				skill_get_time2(sg->skill_id,sg->skill_lv),0);
		break;

	case UNT_SPIDERWEB:	// �X�p�C�_?�E�F�b�u
		if( sg->val2==0 && !bl->has_status(type) )
		{
			int moveblock = ( bl->x/BLOCK_SIZE != src->block_list::x/BLOCK_SIZE || bl->y/BLOCK_SIZE != src->block_list::y/BLOCK_SIZE);
			skill_additional_effect(ss,bl,sg->skill_id,sg->skill_lv,BF_MISC,tick);
			skill_unit_move(*bl,tick,0);
			if(moveblock) bl->delblock();
			bl->x = src->block_list::x;
			bl->y = src->block_list::y;
			if(moveblock) bl->addblock();
			skill_unit_move(*bl,tick,1);
			clif_fixobject(*bl);
			sg->limit = DIFF_TICK(tick,sg->tick)+skill_get_time2(sg->skill_id,sg->skill_lv);
			sg->val2=bl->id;
			sg->interval = -1;
			src->range = 0;
		}
		break;

	case UNT_GRAVITATION:	// Gravitation
		if (battle_check_target(src,bl,BCT_ENEMY)>0)
			skill_attack(BF_MAGIC,ss,src,bl,sg->skill_id,sg->skill_lv,tick,0);		
		break;

/*	default:
		if(config.error_log)
			ShowMessage("skill_unit_onplace: Unknown skill unit id=%d block=%d\n",sg->unit_id,bl->id);
		break;*/
	}

	if (*bl == BL_MOB && ss != bl)
	{	// �X�L���g�p?����MOB�X�L��
		mob_data *md = bl->get_md();
		if (config.mob_changetarget_byskill == 1)
		{
			int target = md->target_id;
			if( *ss == BL_PC )
				md->target_id = ss->id;
			mobskill_use(*md, tick, MSC_SKILLUSED|(sg->skill_id << 16));
			md->target_id = target;
		}
		else
			mobskill_use(*md, tick, MSC_SKILLUSED|(sg->skill_id << 16));
	}

	return 0;
}
/*==========================================
 * �X�L�����j�b�g���痣?����(�������͂��Ă���)�ꍇ
 *------------------------------------------
 */
int skill_unit_onout(struct skill_unit *src, block_list *bl, unsigned long tick)
{
	struct skill_unit_group *sg;
	status_t type;

	nullpo_retr(0, src);
	nullpo_retr(0, bl);
	nullpo_retr(0, sg=src->group);

	type = (status_t)SkillStatusChangeTable[sg->skill_id];

	if( !bl->is_on_map() || !src->alive || //Need to delete the trap if the source died.
		(bl->is_dead() && sg->unit_id != UNT_ANKLESNARE && sg->unit_id != UNT_SPIDERWEB))
		return 0;


	switch(sg->unit_id){
	case UNT_SAFETYWALL:	// �Z�C�t�e�B�E�H�[��
	case UNT_PNEUMA:	// �j���[�}
	case UNT_QUAGMIRE:	// �N�@�O�}�C�A
	case UNT_VOLCANO:	// �{���P�[�m
	case UNT_DELUGE:	// �f�����[�W
	case UNT_VIOLENTGALE:	// �o�C�I�����g�Q�C��
		if (type==SC_QUAGMIRE && *bl==BL_MOB)
			break;
		if (bl->has_status(type) && bl->get_statusvalue2(type).pointer()==src) {
			status_change_end(bl,type,-1);
		}
		break;
	case UNT_ANKLESNARE:	// �A���N���X�l�A
	{
		block_list *target = block_list::from_blid(sg->val2);
		if(target && target == bl){
			status_change_end(bl,SC_ANKLE,-1);
			sg->limit=DIFF_TICK(tick,sg->tick)+1000;
		}
		break;
	}
//	case UNT_LULLABY:	// �q��S
	case UNT_RICHMANKIM:	// �j�����h�̉�
	case UNT_ETERNALCHAOS:	// �i���̍���
	case UNT_DRUMBATTLEFIELD:	// �푾�ۂ̋���
	case UNT_RINGNIBELUNGEN:	// �j�[�x�����O�̎w��
	case UNT_ROKISWEIL:	// ���L�̋���
	case UNT_INTOABYSS:	// �[���̒���
	case UNT_SIEGFRIED:	// �s���g�̃W�[�N�t���[�h
	case UNT_HERMODE:	// Wand of Hermod
		if (bl->has_status(type) && bl->get_statusvalue4(type).pointer()==src) {
			status_change_end(bl,type,-1);
		}
		break;	

//	case UNT_DISSONANCE:	// �s���a��
	case UNT_WHISTLE:	// ���J
	case UNT_ASSASSINCROSS:	// �[�z�̃A�T�V���N���X
	case UNT_POEMBRAGI:	// �u���M�̎�
	case UNT_APPLEIDUN:	// �C�h�D���̗ь�
	case UNT_UGLYDANCE:	// ��������ȃ_���X
	case UNT_HUMMING:	// �n�~���O
	case UNT_FORTUNEKISS:	// �K�^�̃L�X
	case UNT_SERVICEFORYOU:	// �T?�r�X�t�H?��?
	case UNT_DONTFORGETME:	// ����Y��Ȃ��Łc
		if (sg->src_id==bl->id)
		{
			status_change_end(bl,type,-1);
		}
		else if (bl->has_status(type) && bl->get_statusvalue4(type).pointer()==src)
		{
			//sc_data[type].timer = add_timer(20000+tick, status_change_timer, bl->id, type);
			// wrong
			status_change_end(bl,type,-1);
		}
		break;		
	case UNT_BASILICA:	// Basilica
	case UNT_GRAVITATION:	// Gravitation
		if( bl->has_status(type) && bl->get_statusvalue4(type).pointer()==sg)
		{
			status_change_end(bl,type,-1);
		}
		break;

	case UNT_FOGWALL:
		if (bl->has_status(type) && bl->get_statusvalue4(type).pointer()==sg)
		{
			status_change_end(bl,SC_FOGWALL,-1);
			//if( !bl->has_status(SC_BLIND) )
				//sc_data[SC_BLIND].timer = add_timer(
				//	gettick() + 30000, status_change_timer, bl->id, 0);
		}		
		break;

	case UNT_SPIDERWEB:	// �X�p�C�_?�E�F�b�u
	{
		block_list *target = block_list::from_blid(sg->val2);
		if (target && target==bl)
			status_change_end(bl,SC_SPIDERWEB,-1);
		sg->limit = DIFF_TICK(tick,sg->tick)+1000;
		break;
	}

/*	default:
		if(config.error_log)
			ShowMessage("skill_unit_onout: Unknown skill unit id=%d block=%d\n",sg->unit_id,bl->id);
		break;*/
	}

	return 0;
}


/*==========================================
 * �X�L�����j�b�g�̌��E�C�x���g
 *------------------------------------------
 */
int skill_unit_onlimit(struct skill_unit *src,unsigned long tick)
{
	struct skill_unit_group *sg;
	nullpo_retr(0, src);
	nullpo_retr(0, sg=src->group);

	switch(sg->unit_id){
	case 0x81:
		{
			struct skill_unit_group *group=
				skill_unitsetting(block_list::from_blid(sg->src_id),sg->skill_id,sg->skill_lv,
					src->block_list::x,src->block_list::y,1);
			if(group == NULL)
				return 0;
			group->valstring = sg->valstring;
			group->val2=sg->val2;
		}
		break;

	case UNT_ICEWALL:	// �A�C�X�E�H?��
	{
		const unsigned short m=src->block_list::m;
		const unsigned short x=src->block_list::x;
		const unsigned short y=src->block_list::y;
		maps[m].clr_icewall(x,y);
		clif_changemapcell(m,x,y,maps[m].get_type(x,y),1);
		break;
	}
	case UNT_CALLPARTNER:	// ���Ȃ���?������
	{
		map_session_data *sd = NULL;
		map_session_data *p_sd = NULL;
		if((sd = map_session_data::from_blid(sg->src_id)) == NULL)
			return 0;
		if((p_sd = pc_get_partner(*sd)) == NULL)
			return 0;

		pc_setpos(*p_sd,maps[src->block_list::m].mapname,src->block_list::x,src->block_list::y,3);
		break;
	}
	}// end switch
	return 0;
}
/*==========================================
 * �X�L�����j�b�g�̃_��?�W�C�x���g
 *------------------------------------------
 */
int skill_unit_ondamaged(struct skill_unit *src,block_list *bl,
	int damage,unsigned long tick)
{
	struct skill_unit_group *sg;

	nullpo_retr(0, src);
	nullpo_retr(0, sg=src->group);

	switch(sg->unit_id){
	case UNT_ICEWALL:	// �A�C�X�E�H?��
		src->val1-=damage;
		break;
	case UNT_BLASTMINE:	// �u���X�g�}�C��
	case UNT_CLAYMORETRAP:	// �N���C���A?�g���b�v
		skill_blown(bl,src,2); //������΂��Ă݂�
		break;
	default:
		damage = 0;
		break;
	}
	return damage;
}

/*==========================================
 * �X�L���g�p?���i?�Ŏg�p���s�j
 *------------------------------------------
 */
int skill_check_condition(map_session_data *sd,int type)
{
	size_t k;
	long hp,sp,hp_rate,sp_rate, zeny;
	uint32 weapon;
	unsigned short state,spiritball,skill,lv,mhp;
	int	index[10],itemid[10],amount[10];
	int arrow_flag = 0;
	int force_gem_flag = 0;
	int delitem_flag = 1;

	nullpo_retr(0, sd);

	if( config.gm_skilluncond>0 &&
		sd->isGM()>= config.gm_skilluncond &&
		sd->skillitem != sd->skillid)
	{	//GMs don't override the skillItem check, otherwise they can use items without them being consumed! [Skotlex]
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 1;
	}

	if( sd->opt1>0) {
		sd->skill_failed(sd->skillid);
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}
	if( sd->is_90overweight() )
	{
		sd->skill_failed(sd->skillid,SF_WEIGHT);
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}

	if (sd->state.abra_flag)
	{
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		if(type&1) sd->state.abra_flag = 0;
		return 1;
	}

	if (sd->state.produce_flag &&
		(sd->skillid == AM_PHARMACY || sd->skillid == ASC_CDP || sd->skillid == AC_MAKINGARROW || sd->skillid == BS_REPAIRWEAPON))
	{
		sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 0;
	}

	if(sd->skillitem == sd->skillid) {	// �A�C�e���̏ꍇ��?������
		if(!type) //When a target was selected
		{	//Consume items that were skipped in pc_use_item [Skotlex]
			int i = sd->itemindex;
			 if( i >= MAX_INVENTORY ||
				 sd->status.inventory[i].nameid != sd->itemid ||
				 !sd->inventory_data[i]->flag.delay_consume ||
				 sd->status.inventory[i].amount < 1
				)
			{	//Something went wrong, item exploit?
				sd->itemid = sd->itemindex = 0xFFFF;
				return 0;
			}
			//Consume
			sd->itemid = sd->itemindex = 0xFFFF;
			pc_delitem(*sd,i,1,0);
		}
		if (type&1) //Casting finished
			sd->skillitem = sd->skillitemlv = 0xFFFF;
		return 1;
	}
	if( sd->opt1>0 ){
		sd->skill_failed(sd->skillid);
		return 0;
	}

	{
		if( sd->has_status(SC_DIVINA) ||
			sd->has_status(SC_ROKISWEIL) ||
			(sd->has_status(SC_AUTOCOUNTER) && sd->skillid != KN_AUTOCOUNTER) ||
			sd->has_status(SC_STEELBODY) ||
			sd->has_status(SC_BERSERK) ||
			(sd->has_status(SC_MARIONETTE) && sd->skillid != CG_MARIONETTE))
		{
			sd->skill_failed(sd->skillid);
			return 0;	// ?�Ԉُ�Ⓘ?�Ȃ�
		}
	}

	skill = sd->skillid;
	lv = sd->skilllv;
	if (lv <= 0) return 0;
	// for the guild skills [celest]
	if (skill >= 10000 && skill < 10015) skill-= 9500;
	hp = skill_get_hp(skill, lv);	// ����HP
	sp = skill_get_sp(skill, lv);	// ����SP
	if((sd->skillid_old == BD_ENCORE) && skill == sd->skillid_dance)
		sp=sp/2;	//�A���R?������SP�������
	hp_rate = (lv <= 0)? 0:skill_db[skill].hp_rate[lv-1];
	sp_rate = (lv <= 0)? 0:skill_db[skill].sp_rate[lv-1];
	zeny = skill_get_zeny(skill,lv);
	weapon = skill_db[skill].weapon;
	state = skill_db[skill].state;
	spiritball = (lv <= 0)? 0:skill_db[skill].spiritball[lv-1];
	mhp = skill_get_mhp(skill, lv);	// ����HP
	for(k = 0; k < 10; ++k) {
		itemid[k] = skill_db[skill].itemid[k];
		amount[k] = skill_db[skill].amount[k];
	}
	if(mhp > 0)
		hp += (sd->status.max_hp * mhp)/100;
	if(hp_rate > 0)
		hp += (sd->status.hp * hp_rate)/100;
	else
		hp += (sd->status.max_hp * abs(hp_rate))/100;
	if(sp_rate > 0)
		sp += (sd->status.sp * sp_rate)/100;
	else
		sp += (sd->status.max_sp * abs(sp_rate))/100;
	if(sd->dsprate!=100)
		sp=sp*sd->dsprate/100;	// ����SP�C��

	switch(skill) {
	case SA_CASTCANCEL:
		if(sd->skilltimer == -1) {
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case BS_MAXIMIZE:		// �}�L�V�}�C�Y�p��?
	case NV_TRICKDEAD:		// ���񂾂ӂ�
	case TF_HIDING:			// �n�C�f�B���O
	case AS_CLOAKING:		// �N��?�L���O
	case CR_AUTOGUARD:				// �I?�g�K?�h
	case CR_DEFENDER:				// �f�B�t�F���_?
	case ST_CHASEWALK:
	case PA_GOSPEL:
	case TK_RUN:
		if( sd->has_status((status_t)SkillStatusChangeTable[skill]) )
			return 1;			// ��������ꍇ��SP����Ȃ�
		break;
	case AL_WARP:
		if(!(type&2)) //Delete the item when the portal has been selected (type&2). [Skotlex]
			delitem_flag = 0;
		// fall through
	case AL_TELEPORT:
		if(maps[sd->block_list::m].flag.noteleport) {
			clif_skill_teleportmessage(*sd,0);
			return 0;
		}
		break;
	case MO_CALLSPIRITS:	// ?��
		if(sd->spiritball >= lv) {
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case CH_SOULCOLLECT:	// ��?��
		if(sd->spiritball >= 5) {
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case MO_FINGEROFFENSIVE:				//�w?
		if (sd->spiritball > 0 && sd->spiritball < spiritball) {
			spiritball = sd->spiritball;
			sd->spiritball_old = sd->spiritball;
		}
		else sd->spiritball_old = lv;
		break;
	case MO_BODYRELOCATION:
		if(	sd->has_status(SC_EXPLOSIONSPIRITS) )
			spiritball = 0;
		break;
	case MO_CHAINCOMBO:						//�A�ŏ�
		if( !sd->has_status(SC_BLADESTOP) )
		{
			if( !sd->has_status(SC_COMBO) || sd->get_statusvalue1(SC_COMBO).integer() != MO_TRIPLEATTACK )
				return 0;
		}
		break;
	case MO_COMBOFINISH:					//�җ���
		if( !sd->has_status(SC_COMBO) || sd->get_statusvalue1(SC_COMBO).integer() != MO_CHAINCOMBO )
			return 0;
		break;
	case CH_TIGERFIST:						//���Ռ�
		if( (!sd->has_status(SC_COMBO) || sd->get_statusvalue1(SC_COMBO).integer() != MO_COMBOFINISH) && !sd->state.skill_flag)
			return 0;
		break;
	case CH_CHAINCRUSH:						//�A����?
		if( !sd->has_status(SC_COMBO) )
			return 0;
		if( sd->get_statusvalue1(SC_COMBO).integer() != MO_COMBOFINISH && sd->get_statusvalue1(SC_COMBO).integer() != CH_TIGERFIST)
			return 0;
		break;
	case MO_EXTREMITYFIST:					// ���C���e�P��
		if( sd->has_status(SC_BLADESTOP) )
			--spiritball;
		else if (sd->has_status(SC_COMBO) )
		{
			if( sd->get_statusvalue1(SC_COMBO).integer() == MO_COMBOFINISH )
				spiritball = 4;
			else if( sd->get_statusvalue1(SC_COMBO).integer() == CH_TIGERFIST )
				spiritball = 3;
			else if( sd->get_statusvalue1(SC_COMBO).integer() == CH_CHAINCRUSH )
				spiritball = 1;
			// if chain crush came after tiger fist it should be 2...
			// but i'm not sure how to check that yet ^^;
		}
		break;
	case BD_ADAPTATION:				// �A�h���u
		{
			struct skill_unit_group *group=NULL;
			if( !sd->has_status(SC_DANCING) || 
				((group=(struct skill_unit_group*)sd->get_statusvalue2(SC_DANCING).pointer()) && 
				 (skill_get_time(sd->get_statusvalue1(SC_DANCING).integer(),group->skill_lv) - sd->get_statusvalue3(SC_DANCING).integer()*1000) <= skill_get_time2(skill,lv)))
			{ //�_���X���Ŏg�p��5�b�ȏ�̂݁H
				sd->skill_failed(skill);
				return 0;
			}
		}
		break;
	case PR_BENEDICTIO:				// ��?�~��
		{
			int range = 1;
			int c = 0;
			if  (!(type & 1)) {

				maps[sd->block_list::m].foreachinarea( CSkillCheckConditionChar(*sd,skill,c),
					sd->block_list::x, sd->block_list::y, range, BL_PC);
				if (c < 2) {
					sd->skill_failed(skill);
					return 0;
				}
			} else {
				maps[sd->block_list::m].foreachinarea( CSkillCheckConditionUse(*sd,c),
					sd->block_list::x, sd->block_list::y, range, BL_PC);
			}
		}
		break;
	case WE_CALLPARTNER:		// ���Ȃ��Ɉ�������
		if(!sd->status.partner_id){
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case AM_CANNIBALIZE:		// �o�C�I�v�����g
	case AM_SPHEREMINE:			// �X�t�B�A?�}�C��
		if(type&1){
			int c=0;
			int summons[5] = { 1020, 1068, 1118, 1500, 1368 };
			int maxcount = (skill==AM_CANNIBALIZE)? 6-lv : skill_get_maxcount(skill);
			int mob_class = (skill==AM_CANNIBALIZE)? summons[lv-1] :1142;
			if(config.pc_land_skill_limit && maxcount>0)
			{
				c = maps[sd->block_list::m].foreach( CSkillCheckConditionMobmaster(sd->block_list::id, mob_class), BL_MOB);
				if(c >= maxcount){
					sd->skill_failed(skill);
					return 0;
				}
			}
		}
		break;
	case AM_CALLHOMUN:			// �R�[���z�����N���X
	{	//�쐬�ς݂ň�����
		if(sd->hd && sd->hd->status.homun_id > 0 && sd->hd->status.homun_id == sd->status.homun_id && !sd->hd->status.incubate)
			break;
		if( sd->hd && !sd->hd->is_dead() && sd->hd->is_on_map() )
		{
			sd->skill_failed(skill);
			return 0;
		}
		// �쐬�ς݃z�������鎞�ɃG���u���I�����Ă��玸�s
//		size_t i;
//		for(i=0;i<MAX_INVENTORY;i++)
//		{
//			if(sd->status.inventory[i].nameid==7142)
//			{
//				sd->skill_failed(skill);
//				return 0;
//			}
//		}
		break;
	}
	case AM_REST:			// ����
	{
		if( !sd->hd || sd->hd->is_dead() || sd->hd->status.hp < sd->hd->status.max_hp*80/100 )
		{	// �z����HP��MHP��80%�ȏ�ł��邱��
			sd->skill_failed(skill);
			return 0;
		}
		break;
	}
	case AM_RESURRECTHOMUN:			// ���U���N�V�����z�����N���X
	{
		if(sd->hd || sd->hd->status.hp > 0)
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	}
	case MG_FIREWALL:		// �t�@�C�A?�E�H?��
	case WZ_QUAGMIRE:
	case PF_FOGWALL:
		// ?����
		if(config.pc_land_skill_limit) {
			int maxcount = skill_get_maxcount(skill);
			if(maxcount > 0) {
				int i,c;
				for(i=c=0;i<MAX_SKILLUNITGROUP;++i) {
					if(sd->skillunit[i].alive_count > 0 && sd->skillunit[i].skill_id == skill)
						++c;
				}
				if(c >= maxcount) {
					sd->skill_failed(skill);
					return 0;
				}
			}
		}
		break;
	case WZ_FIREPILLAR: // celest
		if (lv <= 5)	// no gems required at level 1-5
			itemid[0] = 0;
		if(config.pc_land_skill_limit) {
			int maxcount = skill_get_maxcount(skill);
			if(maxcount > 0) {
				int i,c;
				for(i=c=0;i<MAX_SKILLUNITGROUP;++i) {
					if(sd->skillunit[i].alive_count > 0 && sd->skillunit[i].skill_id == skill)
						++c;
				}
				if(c >= maxcount) {
					sd->skill_failed(skill);
					return 0;
				}
			}
		}
		break;
	// skills require arrows as of 12/07 [celest]
	case AC_DOUBLE:
	case AC_SHOWER:
	case AC_CHARGEARROW:
	case BA_MUSICALSTRIKE:
	case DC_THROWARROW:
	case SN_SHARPSHOOTING:
	case CG_ARROWVULCAN:
		if(sd->equip_index[10] >= MAX_INVENTORY) {
			clif_arrow_fail(*sd,0);
			return 0;
		}
		arrow_flag = 1;
		break;
	case RG_BACKSTAP:
		if(sd->status.weapon == 11) {
			if (sd->equip_index[10] >= MAX_INVENTORY) {
				clif_arrow_fail(*sd,0);
				return 0;
			}
			arrow_flag = 1;
		}
		break;
	case HW_GANBANTEIN:
		force_gem_flag = 1;
		break;
	case AM_POTIONPITCHER:
	case CR_SLIMPITCHER:
	case MG_STONECURSE:
	case CR_CULTIVATION:
	case SA_FLAMELAUNCHER:
	case SA_FROSTWEAPON:
	case SA_LIGHTNINGLOADER:
	case SA_SEISMICWEAPON:
		delitem_flag = 0;
		break;
	case CG_HERMODE:
	{
		// Hermode's Rod can only be cast near Warp Portals
		// inside Guild Siege maps during WoE times.
		// This skill cancels all positive statuses, aside from Berserk,
		// from all friendly targets except the caster.
		// It will also block any magic spells that are cast upon Hermode's Rod's targets.
		// For the duration of this skill, only the caster can use skills.
		// Hermode's Rod is canceled when the caster leaves its effective range.
		int c = maps[sd->block_list::m].foreachinarea( CSkillCheckConditionHermod(),
			sd->block_list::x, sd->block_list::y, 3, BL_NPC);
		if (c < 1)
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	}
	}// end swirch

	if(!(type&2)){
		if( hp>0 && sd->status.hp < hp) {				// HP�`�F�b�N
			sd->skill_failed(skill,SF_HP);		// HP�s���F���s�ʒm
			return 0;
		}
		if( sp>0 && sd->status.sp < sp) {				// SP�`�F�b�N
			sd->skill_failed(skill,SF_SP);		// SP�s���F���s�ʒm
			return 0;
		}
		if( zeny>0 && sd->status.zeny < (uint32)zeny) {
			sd->skill_failed(skill,SF_ZENY);
			return 0;
		}
		if(!(weapon & (1<<sd->status.weapon) ) ) {
			sd->skill_failed(skill,SF_WEAPON);
			return 0;
		}
		if( spiritball > 0 && sd->spiritball < spiritball) {
			sd->skill_failed(skill);		// �����s��
			return 0;
		}
	}
	switch(state) {
	case ST_HIDING:
		if(!(sd->status.option&2))
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_CLOAKING:
		if( !sd->is_cloaking() )
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_HIDDEN:
		if(!sd->is_hiding())
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_RIDING:
		if(!sd->is_riding())
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_FALCON:
		if(!sd->is_falcon())
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_CART:
		if(!sd->is_carton())
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_SHIELD:
		if(sd->status.shield <= 0) {
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_SIGHT:
		if( !sd->has_status(SC_SIGHT) && type&1)
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_EXPLOSIONSPIRITS:
		if( !sd->has_status(SC_EXPLOSIONSPIRITS) )
		{
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_RECOV_WEIGHT_RATE:
		if(config.natural_heal_weight_rate <= 100 && sd->weight*100 >= sd->max_weight*(uint32)config.natural_heal_weight_rate) {
			sd->skill_failed(skill);
			return 0;
		}
		break;
	case ST_MOVE_ENABLE:
		{
			if( !walkpath_data::is_possible(sd->block_list::m,sd->block_list::x,sd->block_list::y,sd->skillx,sd->skilly,1) )
			{
				sd->skill_failed(skill);
				return 0;
			}
		}
		break;
	case ST_WATER:
		if( maps[sd->block_list::m].flag.rain==1 && config.rainy_waterball==1)
			break;
		if( !maps[sd->block_list::m].is_water(sd->block_list::x,sd->block_list::y) &&
			!sd->has_status(SC_DELUGE) )
		{	//���ꔻ��
			sd->skill_failed(skill);
			return 0;
		}
		break;
	}

	for(k=0;k<10;++k) {
		unsigned short x = lv%11 - 1;
		index[k] = -1;
		if(itemid[k] <= 0)
			continue;
		if(itemid[k] >= 715 && itemid[k] <= 717 && sd->state.no_gemstone && !force_gem_flag)
			continue;
		if(((itemid[k] >= 715 && itemid[k] <= 717) || itemid[k] == 1065)
			&& sd->has_status(SC_INTOABYSS) && !force_gem_flag)
			continue;
		if((skill == AM_POTIONPITCHER ||
			skill == CR_SLIMPITCHER ||
			skill == CR_CULTIVATION) && k != x)
			continue;

		index[k] = pc_search_inventory(*sd,itemid[k]);
		if(index[k] < 0 || sd->status.inventory[index[k]].amount < amount[k])
		{
			sd->skill_failed(skill, (itemid[k]==716)?SF_REDGEM:(itemid[k]==717)?SF_BLUEGEM:SF_MATERIAL);
			return 0;
		}
	}

	if(!(type&1))
		return 1;

	if(delitem_flag) {
		for(k=0;k<10;++k) {
			if(index[k] >= 0)
				pc_delitem(*sd,index[k],amount[k],0);		// �A�C�e������
		}
		if (arrow_flag && config.arrow_decrement)
			pc_delitem(*sd,sd->equip_index[10],1,0);
	}

	if(type&2)
		return 1;

	if(sp > 0) {					// SP����
		sd->status.sp-=sp;
		clif_updatestatus(*sd,SP_SP);
	}
	if(hp > 0) {					// HP����
		sd->status.hp-=hp;
		clif_updatestatus(*sd,SP_HP);
	}
	if(zeny > 0)					// Zeny����
		pc_payzeny(*sd,zeny);
	if(spiritball > 0)				// ��������
		pc_delspiritball(*sd,spiritball,0);


	return 1;
}

/*==========================================
 * �r�����Ԍv�Z
 *------------------------------------------
 */
int skill_castfix(block_list *bl, long time)
{
	nullpo_retr(0, bl);

	if (*bl == BL_PC)
	{
		map_session_data *sd = bl->get_sd();
		// calculate base cast time (reduced by dex)
		if( skill_get_castnodex(sd->skillid, sd->skilllv) <= 0 ) {
			int scale = config.castrate_dex_scale - bl->get_dex();
			if (scale > 0)	// not instant cast
				time = time * (unsigned int)scale / config.castrate_dex_scale;
			else 
				return 0;	// instant cast
		}

		// config cast time multiplier
		if( config.cast_rate < 100 )
			time = time * config.cast_rate / 100;

		// calculate cast time reduced by card bonuses
		if( sd->castrate < 100 )
			time -= time * (100 - sd->castrate) / 100;
	} else if (*bl == BL_PET) { //Skotlex: Simple scaling
		int scale = config.castrate_dex_scale - bl->get_dex();
		if (scale > 0)	// not instant cast
			time = time * scale / config.castrate_dex_scale;
		else return 0;	// instant cast
		
		if (config.cast_rate != 100)
			time = time * config.cast_rate / 100;
	}

	// calculate cast time reduced by skill bonuses
	// �T�t���M�E��
	if( bl->has_status(SC_SUFFRAGIUM) )
	{
		time = time * (100 - bl->get_statusvalue1(SC_SUFFRAGIUM).integer() * 15) / 100;
		status_change_end(bl, SC_SUFFRAGIUM, -1);
	}
	// �u���M�̎�
	if( bl->has_status(SC_POEMBRAGI) )
		time = time * (100 - (bl->get_statusvalue1(SC_POEMBRAGI).integer() * 3 + bl->get_statusvalue2(SC_POEMBRAGI).integer()
			+(bl->get_statusvalue3(SC_POEMBRAGI).integer() >> 16))) / 100;

	// return final cast time
	return (time > 0) ? time : 0;
}
/*==========================================
 * �f�B���C�v�Z
 *------------------------------------------
 */
int skill_delayfix(block_list *bl, long time)
{
	nullpo_retr(0, bl);

	if (*bl == BL_PC)
	{
		map_session_data *sd = bl->get_sd();
		// instant cast attack skills depend on aspd as delay [celest]
		if (time == 0) {
			if (skill_get_type(sd->skillid) == BF_WEAPON)
				time = status_get_adelay (bl)/2;
			else
				time = 300;	// default delay, according to official servers
		} else if (time < 0)
			time = status_get_adelay(bl)/2 - time;	// if set to <0, the aspd delay will be added

		if (config.delay_dependon_dex &&	// dex�̉e�����v�Z����
			!skill_get_delaynodex(sd->skillid, sd->skilllv))	// if skill casttime is allowed to be reduced by dex
		{
			int scale = config.castrate_dex_scale - bl->get_dex();
			if (scale < 0)
				scale = 0;
			time = time * scale / config.castrate_dex_scale;
		}

		if (config.delay_rate != 100)
			time = time * config.delay_rate / 100;

		if (sd->delayrate != 100)
			time = time * sd->delayrate / 100;

		if (time < (long)config.min_skill_delay_limit)	// check minimum skill delay
			time = config.min_skill_delay_limit;
	}

	// �u���M�̎�
	if( bl->has_status(SC_POEMBRAGI) )
		time = time * (100 - (bl->get_statusvalue1(SC_POEMBRAGI).integer() * 3 + bl->get_statusvalue2(SC_POEMBRAGI).integer()
				+ (bl->get_statusvalue3(SC_POEMBRAGI).integer() & 0xffff))) / 100;

	return (time > 0) ? time : 0;
}

/*==========================================
 * �X�L���g�p�iID�w��j
 *------------------------------------------
 */
int skill_use_id(map_session_data *sd, uint32 target_id, unsigned short skill_num, unsigned short skill_lv)
{
	int casttime = 0, delay = 0, skill, range;
	map_session_data* target_sd=NULL;
	int forcecast = 0;	
	block_list *bl;
	unsigned long tick = gettick();

	nullpo_retr(0, sd);
////////////////
// new skill code temporary entrance
if(config._temp_)
{
	sd->start_skill(skill_num, skill_lv, target_id);
	if(config._temp_>1)
		return 0;
}
////////////////
	if( (bl=block_list::from_blid(target_id)) == NULL || !bl->is_on_map() )
	{
		if(config.error_log)
			ShowError("skill target not found %d\n",target_id);
		return 0;
	}
	if(sd->block_list::m != bl->m || sd->is_dead())
		return 0;
	if(sd->skilltimer != -1 && skill_num != SA_CASTCANCEL) //Normally not needed because clif.c checks for it, but the at/char/script commands don't! [Skotlex]
		return 0;
	
	if(skill_not_ok(skill_num, *sd)) // [MouseJstr]
		return 0;

	target_sd = bl->get_sd();
	if( target_sd && skill_num == ALL_RESURRECTION && !target_sd->is_dead())
		return 0;

	// ��?��ُ�i�������A�O�����Ȃǂ̔��������j
	if (sd->opt1 > 0)
		return 0;

	if( (sd->has_status(SC_VOLCANO) && skill_num == WZ_ICEWALL) ||
		(sd->has_status(SC_ROKISWEIL) && skill_num != BD_ADAPTATION) ||
		(sd->has_status(SC_AUTOCOUNTER) && sd->skillid != KN_AUTOCOUNTER) ||
		(sd->has_status(SC_MARIONETTE) && sd->skillid != CG_MARIONETTE) ||
		(sd->has_status(SC_MARIONETTE2) && sd->skillid == CG_MARIONETTE) ||
		sd->has_status(SC_DIVINA) ||
		sd->has_status(SC_STEELBODY) ||
		sd->has_status(SC_BERSERK) )
		return 0;	// ?�Ԉُ�Ⓘ?�Ȃ�

	if( sd->has_status(SC_HERMODE) && skill_get_inf(skill_num) & INF_SUPPORT_SKILL )
		return 0;	//Wand of Hermod blocks only supportive skills. [Skotlex]
	
	if( sd->has_status(SC_BLADESTOP) )
	{
		if( sd->get_statusvalue2(SC_BLADESTOP).integer() == 1 )
			return 0;//���H���ꂽ���Ȃ̂Ń_��
		switch( sd->get_statusvalue1(SC_BLADESTOP).integer() )
		{
			case 1: return 0;
			case 2: if (skill_num != MO_FINGEROFFENSIVE) return 0; else break;
			case 3: if (skill_num != MO_FINGEROFFENSIVE && skill_num != MO_INVESTIGATE) return 0; else break;
			case 4: if (skill_num != MO_FINGEROFFENSIVE && skill_num != MO_INVESTIGATE && skill_num != MO_CHAINCOMBO) return 0; else break;
			case 5: if (skill_num != MO_FINGEROFFENSIVE && skill_num != MO_INVESTIGATE && skill_num != MO_CHAINCOMBO && skill_num!=MO_EXTREMITYFIST) return 0; else break;
		}
	}
	if( sd->has_status(SC_BASILICA) )
	{	// Disallow all other skills in Basilica [celest]
		struct skill_unit_group *sg = (struct skill_unit_group *)sd->get_statusvalue4(SC_BASILICA).pointer();
		// if caster is the owner of basilica
		if (sg && sg->src_id == sd->block_list::id &&
			skill_num == HP_BASILICA) ;	// do nothing
		// otherwise...
		else return 0;
	}
	// ���t/�_���X��
	if( sd->has_status(SC_DANCING) )
	{
		if( sd->get_statusvalue4(SC_DANCING).integer() && skill_num != BD_ADAPTATION) //���t���̓A�h���u�ȊO�s��
			return 0;
		if (skill_num != BD_ADAPTATION && skill_num != BA_MUSICALSTRIKE && skill_num != DC_THROWARROW)
			return 0;
	}		


	//�`�F�C�X�A�n�C�h�A�N���[�L���O���̃X�L��
	if (sd->is_cloaking() && skill_num == TF_HIDING)
		return 0;
	if (sd->status.option & 2 && skill_num != TF_HIDING && skill_num != AS_GRIMTOOTH && skill_num != RG_BACKSTAP && skill_num != RG_RAID)
		return 0;
	if(sd->is_chasewalk() && skill_num != ST_CHASEWALK)
	 	return 0;
	if(skill_get_inf2(skill_num) & INF2_NO_TARGET_SELF && sd->block_list::id == target_id)
		return 0;
	
	//���O�̃X�L��������?����K�v�̂���X�L��
	switch (skill_num)
	{
	case SA_CASTCANCEL:
		if(sd->skillid != skill_num)
		{	//�L���X�g�L�����Z����?��?���Ȃ�
			sd->skillid_old = sd->skillid;
			sd->skilllv_old = sd->skilllv;
		}
		break;

	case BD_ENCORE:					// �A���R?��
		if(!sd->skillid_dance)
		{	//�O��g�p�����x�肪�Ȃ��Ƃ���
			sd->skill_failed(skill_num);
			return 0;
		}
		else
		{
			sd->skillid_old = skill_num;
		}
		break;
	case GD_BATTLEORDER:
	case GD_REGENERATION:
	case GD_RESTORE:
	case GD_EMERGENCYCALL:
		{
			struct guild *g;
			if (!sd->status.guild_id)
				return 0;
			if ((g = guild_search(sd->status.guild_id)) == NULL)
				return 0;
			if (strcmp(sd->status.name,g->master))
				return 0;
			skill_lv = guild_checkskill(*g, skill_num);
			if (skill_lv <= 0) return 0;
		}
		break;
	case BD_LULLABY:				// �q���
	case BD_RICHMANKIM:				// �j�����h�̉�
	case BD_ETERNALCHAOS:			// �i���̍���
	case BD_DRUMBATTLEFIELD:		// ?���ۂ̋���
	case BD_RINGNIBELUNGEN:			// �j?�x�����O�̎w��
	case BD_ROKISWEIL:				// ���L�̋���
	case BD_INTOABYSS:				// �[���̒���
	case BD_SIEGFRIED:				// �s���g�̃W?�N�t��?�h
	case BD_RAGNAROK:				// �_?��?��
	case CG_MOONLIT:				// ������̐�ɗ�����Ԃт�
	{
		range = 1;
		int c = 0;
		maps[sd->block_list::m].foreachinarea( CSkillCheckConditionChar(*sd,skill_num,c),
			sd->block_list::x, sd->block_list::y, range, BL_PC);
		if(c < 1)
		{
			sd->skill_failed(skill_num);
			return 0;
		}
		else if(c == 99)
		{	//�����s�v�ݒ肾����
			;
		}
		else
		{
			sd->skilllv = (c + skill_lv)/2;
		}
		break;
	}
	}//end switch

	sd->skillid = skill_num;
	sd->skilllv = skill_lv;
	if (!skill_check_condition(sd,0))
	{
		return 0;	
	}
	else
	{
		int check_range_flag = 0;

		// �˒��Ə�Q���`�F�b�N
		range = skill_get_range(skill_num,skill_lv);
		if(range < 0)
			range = sd->get_range() - (range + 1);
		// be lenient if the skill was cast before we have moved to the correct position [Celest]
		if( sd->is_walking() )
			++range;
		else check_range_flag = 1;
		if(!battle_check_range(sd,bl,range))
		{
			if(check_range_flag && battle_check_range(sd,bl,range + 1))
			{
				static const signed char mask[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
				dir_t dir = sd->get_direction(*bl);
				sd->walktoxy (sd->block_list::x + mask[dir][0], sd->block_list::y + mask[dir][1]);
			}
			else
				return 0;
		}
	}

	if ((skill_num != MO_CHAINCOMBO &&
		skill_num != MO_COMBOFINISH &&
		skill_num != MO_EXTREMITYFIST &&
		skill_num != CH_TIGERFIST &&
		skill_num != CH_CHAINCRUSH) ||
		(skill_num == CH_CHAINCRUSH && sd->state.skill_flag) ||
		(skill_num == MO_EXTREMITYFIST && sd->state.skill_flag) )
		sd->stop_attack();

	casttime = skill_castfix(sd, skill_get_cast(skill_num, skill_lv));
	if (skill_num != SA_MAGICROD)
		delay = skill_delayfix(sd, skill_get_delay(skill_num, skill_lv));
	sd->state.skillcastcancel = skill_get_castcancel(skill_num);

	switch (skill_num)
	{	// ���������?�����K�v
	case ALL_RESURRECTION:	// ���U���N�V����
		if(!target_sd && bl->is_undead())
		{	// �G���A���f�b�h�Ȃ�
			forcecast = 1;	// �^?���A���f�b�g�Ɠ����r������
			casttime = skill_castfix(sd, skill_get_cast(PR_TURNUNDEAD, skill_lv));
		}
		break;

	case MO_FINGEROFFENSIVE:	// �w?
		casttime += casttime * ((skill_lv > sd->spiritball) ? sd->spiritball : skill_lv);
		break;

	case MO_CHAINCOMBO:		// �A�ŏ�
		target_id = sd->target_id;
		if( sd->has_status(SC_BLADESTOP) )
		{
			if( sd->get_statusvalue4(SC_BLADESTOP).pointer() )
				target_id = ((block_list *)sd->get_statusvalue4(SC_BLADESTOP).pointer())->id;
		}
		break;

	case MO_COMBOFINISH:	// �җ���
	case CH_CHAINCRUSH:		// �A����?
	case CH_TIGERFIST:		// ���Ռ�
		target_id = sd->target_id;
		break;

// -- moonsoul	(altered to allow proper usage of extremity from new champion combos)
//
	case MO_EXTREMITYFIST:	// ���C���e�P��
		if( sd->has_status(SC_COMBO) &&
			(sd->get_statusvalue1(SC_COMBO).integer() == MO_COMBOFINISH ||
			sd->get_statusvalue1(SC_COMBO).integer() == CH_TIGERFIST ||
			sd->get_statusvalue1(SC_COMBO).integer() == CH_CHAINCRUSH))
		{
			casttime = 0;
			target_id = sd->target_id;
		}
		forcecast = 1;
		break;

	case SA_MAGICROD:
	case SA_SPELLBREAKER:
		forcecast = 1;
		break;

	case WE_MALE:
	case WE_FEMALE:
		{
			map_session_data *p_sd = pc_get_partner(*sd);
			if (p_sd == NULL)
				return 0;
			if (skill_num == WE_MALE && sd->status.hp <= ((15*sd->status.max_hp)/100))	// Requires more than 15% of Max HP for WE_MALE
				return 0;
			else if (skill_num == WE_FEMALE && sd->status.sp <= ((15*sd->status.max_sp)/100))	// Requires more than 15% of Max SP for WE_FEMALE
				return 0;
			target_id = p_sd->block_list::id;
			//range������1��?��
			if (!battle_check_range(sd, p_sd, skill_get_range(skill_num,skill_lv)))
				return 0;
		}
		break;

	// parent-baby skills
	case WE_BABY:
	case WE_CALLPARENT:
		{
			map_session_data *f_sd = pc_get_father(*sd);
			map_session_data *m_sd = pc_get_mother(*sd);
			
			// set target as any one of the parent
			if (f_sd) target_id = f_sd->block_list::id;
			else if (m_sd) target_id = m_sd->block_list::id;
			else return 0;	// neither are found

			// skip range check
			//range������1��?��
			//range = skill_get_range(skill_num,skill_lv);
			//if(!battle_check_range(sd,&p_sd->bl,range))
			//	return 0;
		}
		break;

	case WE_CALLBABY:
		{
			map_session_data *p_sd = pc_get_child(*sd);
			if (p_sd == NULL)
				return 0;
			target_id = p_sd->block_list::id;
			//range������1��?��
			if(!battle_check_range(sd, p_sd, skill_get_range(skill_num,skill_lv)))
				return 0;
		}
		break;

	case HP_BASILICA:		// �o�W���J
		if (skill_check_unit_range(sd->block_list::m,sd->block_list::x,sd->block_list::y,sd->skillid,sd->skilllv))
		{
			sd->skill_failed(sd->skillid);
			return 0;
		}
		if( skill_check_unit_range2(sd->block_list::m,sd->block_list::x,sd->block_list::y,sd->skillid,sd->skilllv,BL_ALL) )
		{
			sd->skill_failed(sd->skillid);
			return 0;
		}
		// cancel Basilica if already in effect
		if ( sd->has_status(SC_BASILICA) )
		{
			struct skill_unit_group *sg = (struct skill_unit_group *)sd->get_statusvalue4(SC_BASILICA).pointer();
			if (sg && sg->src_id == sd->block_list::id)
			{
				status_change_end(sd,SC_BASILICA,-1);
				skill_delunitgroup (*sg);
				return 0;
			}
		}
		break;

	case GD_BATTLEORDER:
	case GD_REGENERATION:
	case GD_RESTORE:
	case GD_EMERGENCYCALL:
		casttime = 1000; // temporary [Celest]
		break;
	}

	//�������C�Y?�ԂȂ�L���X�g�^�C����1/3
	if ( sd->has_status(SC_MEMORIZE) && casttime > 0)
	{
		casttime = casttime/2;
		if( --sd->get_statusvalue2(SC_MEMORIZE).integer() <= 0 )
			status_change_end(sd, SC_MEMORIZE, -1);
	}

	if (config.pc_skill_log)
		ShowMessage("PC %d skill use target_id=%d skill=%d lv=%d cast=%d\n",sd->block_list::id,target_id,skill_num,skill_lv,casttime);

	if (casttime > 0 || forcecast) { // �r�����K�v 
		struct mob_data *md;
		if(sd->disguise_id)
		{	// [Valaris]
			clif_skillcasting(*sd,sd->block_list::id, target_id, 0,0, skill_num,0);
			clif_skillcasting(*sd,sd->block_list::id|FLAG_DISGUISE, target_id, 0,0, skill_num,casttime);
		}
		else
			clif_skillcasting(*sd, sd->block_list::id, target_id, 0,0, skill_num,casttime);
		// �r����?�����X�^?
		md = bl->get_md();
		if( md && mob_db[md->class_].mode & 0x10 && !md->is_attacking() && sd->invincible_timer == -1)
		{
			md->target_id = sd->block_list::id;
			md->state.targettype = ATTACKABLE;
			md->min_chase = 13;
		}
	}

	sd->skilltarget = target_id;
	sd->skillx = 0;
	sd->skilly = 0;
	sd->canact_tick = tick + casttime + delay;
	sd->canmove_tick = tick;

	//if (!(config.pc_cloak_check_type & 2) && //Why non-type 2 will not be uncloaked by skills? [Skotlex]
	if( sd->has_status(SC_CLOAKING) && sd->skillid != AS_CLOAKING )
		status_change_end(sd,SC_CLOAKING,-1);
	if (casttime > 0)
	{
		sd->skilltimer = add_timer(tick + casttime, skill_castend_id, sd->block_list::id, 0);
		if ((skill = sd->skill_check(SA_FREECAST)) > 0)
			status_calc_speed (*sd, SA_FREECAST, skill, 1);
		else
			sd->stop_walking(0);
	}
	else
	{
		sd->state.skillcastcancel = 0;	// �r���̖������̂̓L�����Z������Ȃ�
		if (skill_num != SA_CASTCANCEL)
			sd->skilltimer = -1;
		skill_castend_id(sd->skilltimer,tick,sd->block_list::id,0);
	}

	return 0;
}

/*==========================================
 * �X�L���g�p�i�ꏊ�w��j
 *------------------------------------------
 */
int skill_use_pos( map_session_data *sd, int skill_x, int skill_y, unsigned short skill_num, unsigned short skill_lv)
{
	block_list bl;
	int casttime = 0, delay = 0, skill, range;
	unsigned long tick = gettick();
	nullpo_retr(0, sd);

	if( sd->is_dead() )
		return 0;
	if (sd->skilltimer != -1) //Normally not needed since clif.c checks for it, but at/char/script commands don't! [Skotlex]
		return 0;
	if (skill_not_ok(skill_num, *sd)) // [MoueJstr]
		return 0;
	if (skill_num == WZ_ICEWALL && maps[sd->block_list::m].flag.noicewall && !maps[sd->block_list::m].flag.pvp)  { // noicewall flag [Valaris]
		sd->skill_failed(sd->skillid);
		return 0;
	}
	if( !maps[sd->block_list::m].is_passable(skill_x, skill_y) )
	{	//prevent casting traps on non-walkable areas. [Skotlex] 
		sd->skill_failed(skill_num);
		return 0;
	}
	
	if (sd->opt1 > 0)
		return 0;
	if( sd->has_status(SC_DIVINA) ||
		sd->has_status(SC_ROKISWEIL) ||
		sd->has_status(SC_AUTOCOUNTER) ||
		sd->has_status(SC_STEELBODY) ||
		sd->has_status(SC_DANCING) ||
		sd->has_status(SC_BERSERK)  ||
		sd->has_status(SC_MARIONETTE) ||
		sd->has_status(SC_BLADESTOP) )
		return 0;

	if( sd->has_status(SC_HERMODE) && skill_get_inf(skill_num) & INF_SUPPORT_SKILL)
		return 0;	//Wand of Hermod blocks only supportive skills. [Skotlex]

	if( sd->has_status(SC_BASILICA) )
	{
		struct skill_unit_group *sg = (struct skill_unit_group *)sd->get_statusvalue4(SC_BASILICA).pointer();
		// if caster is the owner of basilica
		if (sg && sg->src_id == sd->block_list::id &&
			skill_num == HP_BASILICA) ;	// do nothing
		// otherwise...
		else return 0;
	}		


	if(sd->status.option & 2)
		return 0;

	sd->skillid = skill_num;
	sd->skilllv = skill_lv;
	if (skill_lv <= 0) return 0;
	sd->skillx = skill_x;
	sd->skilly = skill_y;
	if (!skill_check_condition(sd,0)) return 0;

	bl.m = sd->block_list::m;
	bl.x = skill_x;
	bl.y = skill_y;

	{
		int check_range_flag = 0;

		// �˒��Ə�Q���`�F�b�N
		range = skill_get_range(skill_num,skill_lv);
		if(range < 0)
			range = sd->get_range() - (range + 1);
		// be lenient if the skill was cast before we have moved to the correct position [Celest]
		if( sd->is_walking() )
			++range;
		else check_range_flag = 1;
		if(!battle_check_range(sd,&bl,range)) {
			if (check_range_flag && battle_check_range(sd,&bl,range + 1)) {
				static const signed char mask[8][2] = {{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1},{-1,0},{-1,1}};
				dir_t dir = sd->get_direction(bl);
				sd->walktoxy(sd->block_list::x + mask[dir][0], sd->block_list::y + mask[dir][1]);
			} else
				return 0;
		}
	}

	sd->stop_attack();

	casttime = skill_castfix(sd, skill_get_cast( skill_num,skill_lv) );
	delay = skill_delayfix(sd, skill_get_delay( skill_num,skill_lv) );
	sd->state.skillcastcancel = skill_db[skill_num].castcancel;

	if (config.pc_skill_log)
		ShowMessage("PC %d skill use target_pos=(%d,%d) skill=%d lv=%d cast=%d\n",sd->block_list::id,skill_x,skill_y,skill_num,skill_lv,casttime);

	//�������C�Y?�ԂȂ�L���X�g�^�C����1/3
	if ( sd->has_status(SC_MEMORIZE) && casttime > 0)
	{
		casttime = casttime/3;
		if( --sd->get_statusvalue2(SC_MEMORIZE).integer()<=0 )
			status_change_end(sd, SC_MEMORIZE, -1);
	}
	
	if( casttime>0 ) {	// �r�����K�v
		if(sd->disguise_id)
		{	// [Valaris]
			clif_skillcasting(*sd,sd->block_list::id, 0, skill_x,skill_y, skill_num, casttime);
			clif_skillcasting(*sd,sd->block_list::id|FLAG_DISGUISE, 0, skill_x,skill_y, skill_num,casttime);
		}
		else
			clif_skillcasting(*sd, sd->block_list::id, 0, skill_x, skill_y, skill_num, casttime);
	}
	
	sd->skilltarget	= 0;
	sd->canact_tick = tick + casttime + delay;
	sd->canmove_tick = tick;
	//if (!(config.pc_cloak_check_type&2) &&
	if( sd->has_status(SC_CLOAKING) )
		status_change_end(sd,SC_CLOAKING,-1);
	
	if (casttime > 0)
	{
		sd->skilltimer = add_timer(tick + casttime, skill_castend_pos, sd->block_list::id, 0);
		if ((skill = sd->skill_check(SA_FREECAST)) > 0)
			status_calc_speed (*sd, SA_FREECAST, skill, 1);
		else
			sd->stop_walking(0);
	} else {
		sd->state.skillcastcancel = 0;	// �r���̖������̂̓L�����Z������Ȃ�
		sd->skilltimer = -1;
		skill_castend_pos(sd->skilltimer,tick,sd->block_list::id,0);
	}
	//�}�W�b�N�p��?��?�ʏI��
	if( skill_get_unit_id(skill_num, 0) != 0x86 && sd->has_status(SC_MAGICPOWER) )
		status_change_end(sd,SC_MAGICPOWER,-1);
	
	return 0;
}

/*==========================================
 * �X�L���r���L�����Z��
 *------------------------------------------
 */
int skill_castcancel(block_list *bl, int type)
{
	int ret=0;

	nullpo_retr(0, bl);

	if (*bl == BL_PC)
	{
		map_session_data *sd = (map_session_data *)bl;
		unsigned long tick = gettick();
		nullpo_retr(0, sd);
		sd->canact_tick = tick;
		sd->canmove_tick = tick;
		if (sd->skilltimer != -1)
		{

			if( (ret=sd->skill_check(SA_FREECAST)) > 0)	// borrow ret as temp variable
				status_calc_speed(*sd,SA_FREECAST,ret,0);

			if (!type)
			{
				if (skill_get_inf( sd->skillid ) & INF_GROUND_SKILL)
					ret = delete_timer( sd->skilltimer, skill_castend_pos );
				else
					ret = delete_timer( sd->skilltimer, skill_castend_id );
				if (ret < 0)
					ShowError("delete timer error : (old) skillid : %d\n", sd->skillid_old);
			}
			else
			{
				if (skill_get_inf( sd->skillid_old ) & INF_GROUND_SKILL)
					ret = delete_timer( sd->skilltimer, skill_castend_pos );
				else
					ret = delete_timer( sd->skilltimer, skill_castend_id );
				if (ret < 0)
					ShowMessage("delete timer error : skillid : %d\n",sd->skillid_old);
			}
			sd->skilltimer = -1;
			clif_skillcastcancel(*bl);
		}
		return 0;
	}
	else if ( *bl == BL_MOB)
	{
		struct mob_data *md = (struct mob_data *)bl;
		nullpo_retr(0, md);
		if (md->skilltimer != -1)
		{
			if (skill_get_inf( md->skillid ) & INF_GROUND_SKILL)
				ret = delete_timer( md->skilltimer, mobskill_castend_pos );
			else
				ret = delete_timer( md->skilltimer, mobskill_castend_id );
			md->skilltimer = -1;
			clif_skillcastcancel(*bl);
		}
		if (ret < 0)
			ShowMessage("delete timer error : skillid : %d\n",md->skillid);
		return 0;
	}
	else if (*bl == BL_PET)
	{
		pet_data *pd = bl->get_pd();
		pd->state.casting_flag = 0;
		clif_skillcastcancel(*pd);
		if( pd->is_walking() )
			pd->set_idle();

		//The timer is not deleted as the pet's attack will be resumed.
		return 0;
	}
	return 1;
}
/*=========================================
 * �u�����f�B�b�V���X�s�A ������?����
 *----------------------------------------
 */
void skill_brandishspear_first(struct square *tc,int dir,int x,int y){

	nullpo_retv(tc);

	if(dir == 0)
	{
		tc->val1[0]=x-2;
		tc->val1[1]=x-1;
		tc->val1[2]=x;
		tc->val1[3]=x+1;
		tc->val1[4]=x+2;
		tc->val2[0]=
		tc->val2[1]=
		tc->val2[2]=
		tc->val2[3]=
		tc->val2[4]=y-1;
	}
	else if(dir==2)
	{
		tc->val1[0]=
		tc->val1[1]=
		tc->val1[2]=
		tc->val1[3]=
		tc->val1[4]=x+1;
		tc->val2[0]=y+2;
		tc->val2[1]=y+1;
		tc->val2[2]=y;
		tc->val2[3]=y-1;
		tc->val2[4]=y-2;
	}
	else if(dir==4)
	{
		tc->val1[0]=x-2;
		tc->val1[1]=x-1;
		tc->val1[2]=x;
		tc->val1[3]=x+1;
		tc->val1[4]=x+2;
		tc->val2[0]=
		tc->val2[1]=
		tc->val2[2]=
		tc->val2[3]=
		tc->val2[4]=y+1;
	}
	else if(dir==6)
	{
		tc->val1[0]=
		tc->val1[1]=
		tc->val1[2]=
		tc->val1[3]=
		tc->val1[4]=x-1;
		tc->val2[0]=y+2;
		tc->val2[1]=y+1;
		tc->val2[2]=y;
		tc->val2[3]=y-1;
		tc->val2[4]=y-2;
	}
	else if(dir==1)
	{
		tc->val1[0]=x-1;
		tc->val1[1]=x;
		tc->val1[2]=x+1;
		tc->val1[3]=x+2;
		tc->val1[4]=x+3;
		tc->val2[0]=y-4;
		tc->val2[1]=y-3;
		tc->val2[2]=y-1;
		tc->val2[3]=y;
		tc->val2[4]=y+1;
	}
	else if(dir==3)
	{
		tc->val1[0]=x+3;
		tc->val1[1]=x+2;
		tc->val1[2]=x+1;
		tc->val1[3]=x;
		tc->val1[4]=x-1;
		tc->val2[0]=y-1;
		tc->val2[1]=y;
		tc->val2[2]=y+1;
		tc->val2[3]=y+2;
		tc->val2[4]=y+3;
	}
	else if(dir==5)
	{
		tc->val1[0]=x+1;
		tc->val1[1]=x;
		tc->val1[2]=x-1;
		tc->val1[3]=x-2;
		tc->val1[4]=x-3;
		tc->val2[0]=y+3;
		tc->val2[1]=y+2;
		tc->val2[2]=y+1;
		tc->val2[3]=y;
		tc->val2[4]=y-1;
	}
	else if(dir==7)
	{
		tc->val1[0]=x-3;
		tc->val1[1]=x-2;
		tc->val1[2]=x-1;
		tc->val1[3]=x;
		tc->val1[4]=x+1;
		tc->val2[1]=y;
		tc->val2[0]=y+1;
		tc->val2[2]=y-1;
		tc->val2[3]=y-2;
		tc->val2[4]=y-3;
	}

}

/*=========================================
 * �u�����f�B�b�V���X�s�A �������� ��??��
 *-----------------------------------------
 */
void skill_brandishspear_dir(struct square *tc,int dir,int are){

	int c;

	nullpo_retv(tc);

	for(c=0;c<5;++c){
		if(dir==0){
			tc->val2[c]+=are;
		}else if(dir==1){
			tc->val1[c]-=are; tc->val2[c]+=are;
		}else if(dir==2){
			tc->val1[c]-=are;
		}else if(dir==3){
			tc->val1[c]-=are; tc->val2[c]-=are;
		}else if(dir==4){
			tc->val2[c]-=are;
		}else if(dir==5){
			tc->val1[c]+=are; tc->val2[c]-=are;
		}else if(dir==6){
			tc->val1[c]+=are;
		}else if(dir==7){
			tc->val1[c]+=are; tc->val2[c]+=are;
		}
	}
}

/*==========================================
 * �f�B�{?�V���� �L?�m�F
 *------------------------------------------
 */
void skill_devotion(map_session_data *md,uint32 target)
{
	// ?�m�F
	int n;

	nullpo_retv(md);

	for(n=0; n<5; ++n)
	{
		if(md->dev.val1[n])
		{
			map_session_data *sd = map_session_data::from_blid(md->dev.val1[n]);
			// ���肪������Ȃ� // ������f�B�{���Ă�̂���������Ȃ� // ����������Ă�
			if( sd == NULL || 
				md->block_list::id != (uint32)sd->get_statusvalue1(SC_DEVOTION).integer() || 
				skill_devotion3(md,md->dev.val1[n]) )
			{
				skill_devotion_end(md,sd,n);
			}
		}
	}
}
void skill_devotion2(block_list *bl,uint32 crusader)
{
	// ��f�B�{?�V������?�������̋����`�F�b�N
	map_session_data *sd = map_session_data::from_blid(crusader);

	nullpo_retv(bl);

	if(sd) skill_devotion3(sd,bl->id);
}
int skill_devotion3(block_list *bl,uint32 target)
{
	// �N���Z��?�������̋����`�F�b�N
	map_session_data *md;
	map_session_data *sd;
	int n,r=0;

	nullpo_retr(1, bl);
	md = (map_session_data *)bl;

	if ((sd = map_session_data::from_blid(target))==NULL)
		return 1;
	else
		r = distance(*bl,*sd);

	if(md->skill_check(CR_DEVOTION)+6 < r){	// ���e��?�𒴂��Ă�
		for(n=0; n<5; ++n)
			if(md->dev.val1[n]==target)
				md->dev.val2[n]=0;	// ���ꂽ���́A?��؂邾��
		clif_devotion(*md,sd->block_list::id);
		return 1;
	}
	return 0;
}

void skill_devotion_end(map_session_data *md,map_session_data *sd,uint32 target)
{
	// �N���Z�Ɣ�f�B�{�L�����̃��Z�b�g
	nullpo_retv(md);
	nullpo_retv(sd);

	md->dev.val1[target]=md->dev.val2[target]=0;
	//status_change_end(*sd,SC_DEVOTION,-1);
	sd->get_statusvalue1(SC_DEVOTION)=0;
	sd->get_statusvalue2(SC_DEVOTION)=0;
	clif_status_change(*sd,SC_DEVOTION,0);
	clif_devotion(*md,sd->block_list::id);
}
/*==========================================
 * �I?�g�X�y��
 *------------------------------------------
 */
int skill_autospell(map_session_data *sd,int skillid)
{
	int skilllv;
	int maxlv=1,lv;

	nullpo_retr(0, sd);

	skilllv = sd->skill_check(SA_AUTOSPELL);
	if(skilllv <= 0) return 0;

	if(skillid==MG_NAPALMBEAT)	maxlv=3;
	else if(skillid==MG_COLDBOLT || skillid==MG_FIREBOLT || skillid==MG_LIGHTNINGBOLT){
		if(skilllv==2) maxlv=1;
		else if(skilllv==3) maxlv=2;
		else if(skilllv>=4) maxlv=3;
	}
	else if(skillid==MG_SOULSTRIKE){
		if(skilllv==5) maxlv=1;
		else if(skilllv==6) maxlv=2;
		else if(skilllv>=7) maxlv=3;
	}
	else if(skillid==MG_FIREBALL){
		if(skilllv==8) maxlv=1;
		else if(skilllv>=9) maxlv=2;
	}
	else if(skillid==MG_FROSTDIVER) 
		maxlv=1;
	else 
		return 0;

	if(maxlv > (lv=sd->skill_check(skillid)))
		maxlv = lv;

	status_change_start(sd,SC_AUTOSPELL,skilllv,skillid,maxlv,0,	// val1:�X�L��ID val2:�g�p�ő�Lv
		skill_get_time(SA_AUTOSPELL,skilllv),0);// �ɂ��Ă݂�����bscript�������Ղ�???�H
	return 0;
}

int skill_gangsterparadise(map_session_data *sd ,int type)
{
	int range=1;
	int c=0;

	nullpo_retr(0, sd);

	if(sd->skill_check(RG_GANGSTER) <= 0)
		return 0;

	if(type==1) {// ����������?��

		c = maps[sd->block_list::m].foreachinarea( CSkillGangsterCount(),
			sd->block_list::x, sd->block_list::y, range, BL_PC);
		if(c > 1)
		{	// �M�����O�X�^?���������玩���ɂ��M�����O�X�^??���t?
			maps[sd->block_list::m].foreachinarea( CSkillGangsterIn(),
				sd->block_list::x, sd->block_list::y, range, BL_PC);
			sd->state.gangsterparadise = 1;
		}
		return 0;
	}
	else if(type==0)
	{	// �����オ�����Ƃ���?�� 
		c = maps[sd->block_list::m].foreachinarea( CSkillGangsterCount(),
			sd->block_list::x, sd->block_list::y, range, BL_PC);
		if(c < 2)
		{
			maps[sd->block_list::m].foreachinarea( CSkillGangsterOut(),
				sd->block_list::x, sd->block_list::y, range, BL_PC);
		}
		sd->state.gangsterparadise = 0;
		return 0;
	}
	return 0;
}
/*==========================================
 * Taekwon TK_HPTIME and TK_SPTIME skills [Dralnu]
 *------------------------------------------
 */

class CSkillRestCount : public CMapProcessor
{
public:
	CSkillRestCount()	{}
	~CSkillRestCount()	{}
	virtual int process(block_list& bl) const
	{
		map_session_data &sd=(map_session_data&)bl;
		if( sd.is_sitting() && (sd.skill_check(TK_HPTIME) > 0 || sd.skill_check(TK_SPTIME) > 0) )
			return 1;
		return 0;
	}
};

class CSkillRestIn : public CMapProcessor
{
public:
	CSkillRestIn()	{}
	~CSkillRestIn()	{}
	virtual int process(block_list& bl) const
	{
		map_session_data &sd=(map_session_data&)bl;
		if( sd.is_sitting() && (sd.skill_check(TK_HPTIME) > 0 || sd.skill_check(TK_SPTIME) > 0 ))
		{
			sd.state.rest=1;
			status_calc_pc(sd,0);
		}		
		return 0;
	}
};
class CSkillRestOut : public CMapProcessor
{
public:
	CSkillRestOut()	{}
	~CSkillRestOut()	{}
	virtual int process(block_list& bl) const
	{
		map_session_data &sd=(map_session_data&)bl;
		if(sd.state.rest != 0){
			sd.state.rest=0;
		}		
		return 0;
	}
};
int skill_rest(map_session_data &sd ,int type)
{
	int range=1;
	int c_r=0;

	if(sd.skill_check(TK_HPTIME) <= 0 && sd.skill_check(TK_SPTIME) <= 0)
		return 0;

	if(type==1)
	{	//When you sit down
		c_r = maps[sd.block_list::m].foreachinarea( CSkillRestCount(),
			sd.block_list::x, sd.block_list::y, range, BL_PC);
		if(c_r > 1)
		{
			maps[sd.block_list::m].foreachinarea( CSkillRestIn(),
				sd.block_list::x, sd.block_list::y, range, BL_PC);
			sd.state.rest = 1;
			status_calc_pc(sd,0);
		}
		return 0;
	}
	else if(type==0)
	{	//When you stand up
		c_r = maps[sd.block_list::m].foreachinarea( CSkillRestCount(),
			sd.block_list::x, sd.block_list::y, range, BL_PC);
		if(c_r < 2)
		{
			maps[sd.block_list::m].foreachinarea( CSkillRestIn(),
				sd.block_list::x, sd.block_list::y, range, BL_PC);
		}
		sd.state.rest = 0;
		status_calc_pc(sd,0);
		return 0;
	}
	return 0;
}



/*==========================================
 * �o�W���J�̃Z����ݒ肷��
 *------------------------------------------
 */

void skill_basilica_cell(struct skill_unit *unit, bool on)
{
	int i,x,y,range = skill_get_unit_range(HP_BASILICA);
	int size = range*2+1;

	for (i=0;i<size*size;++i)
	{
		x = unit->block_list::x+(i%size-range);
		y = unit->block_list::y+(i/size-range);
		if(on)
			maps[unit->block_list::m].set_basilica(x,y);
		else
			maps[unit->block_list::m].clr_basilica(x,y);
	}
}

/*==========================================
 *
 *------------------------------------------
 */
int skill_clear_element_field(block_list *bl)
{
	nullpo_retr(0, bl);


	int i,max,skillid;
	map_session_data *sd=bl->get_sd();
	mob_data *md=bl->get_md();
	
	if ( md )
	{
		max = MAX_MOBSKILLUNITGROUP;
	}
	else if( sd )
	{
		max = MAX_SKILLUNITGROUP;
	}
	else
		return 0;

	for (i=0;i<max;++i) {
		if(sd){
			skillid=sd->skillunit[i].skill_id;
			if(skillid==SA_DELUGE||skillid==SA_VOLCANO||skillid==SA_VIOLENTGALE||skillid==SA_LANDPROTECTOR)
				skill_delunitgroup(sd->skillunit[i]);
		}else if(md){
			skillid=md->skillunit[i].skill_id;
			if(skillid==SA_DELUGE||skillid==SA_VOLCANO||skillid==SA_VIOLENTGALE||skillid==SA_LANDPROTECTOR)
				skill_delunitgroup(md->skillunit[i]);
		}
	}
	return 0;
}

/*==========================================
 * �X�e?�^�X�ُ�I��
 *------------------------------------------
 */
int skill_enchant_elemental_end (block_list *bl, int type)
{
	nullpo_retr(0, bl);

	if (type != SC_ENCPOISON && bl->has_status(SC_ENCPOISON) )			// �G���`�����g�|�C�Y������
		status_change_end(bl, SC_ENCPOISON, -1);
	if (type != SC_ASPERSIO && bl->has_status(SC_ASPERSIO) )			// �A�X�y���V�I����
		status_change_end(bl, SC_ASPERSIO, -1);
	if (type != SC_FLAMELAUNCHER && bl->has_status(SC_FLAMELAUNCHER) )	// �t���C�������`������
		status_change_end(bl, SC_FLAMELAUNCHER, -1);
	if (type != SC_FROSTWEAPON && bl->has_status(SC_FROSTWEAPON) )		// �t���X�g�E�F�|������
		status_change_end(bl, SC_FROSTWEAPON, -1);
	if (type != SC_LIGHTNINGLOADER && bl->has_status(SC_LIGHTNINGLOADER) )	// ���C�g�j���O��?�_?����
		status_change_end(bl, SC_LIGHTNINGLOADER, -1);
	if (type != SC_SEISMICWEAPON && bl->has_status(SC_SEISMICWEAPON) )	// �T�C�X�~�b�N�E�F�|������
		status_change_end(bl, SC_SEISMICWEAPON, -1);

	return 0;
}

// �N��?�L���O?���i����Ɉړ��s�\�n?�����邩�j
int skill_check_cloaking(block_list *bl)
{
	map_session_data *sd = NULL;
	static int dx[] = { 0, 1, 0, -1, -1,  1, 1, -1}; //optimized by Lupus
	static int dy[] = {-1, 0, 1,  0, -1, -1, 1,  1};
	int end=1;
	size_t i;
	nullpo_retr(1, bl);

	if (*bl == BL_PC) {
		nullpo_retr(1, sd = (map_session_data *)bl);
		if (!config.pc_cloak_check_type
			|| config.pc_cloak_check_type == 2) // If it's No it shouldn't be checked
			return 0;
	} else if (*bl == BL_MOB && !config.monster_cloak_check_type)
		return 0;

	for (i = 0; i < 8; ++i)
	{
		if( !maps[bl->m].is_passable(bl->x+dx[i], bl->y+dy[i]) )
		{
			end = 0;
			break;
		}
	}
	if(end){
		if ((sd && sd->skill_check(AS_CLOAKING)<3) || *bl == BL_MOB) {
			status_change_end(bl, SC_CLOAKING, -1);
		}
		else if (sd && sd->get_statusvalue3(SC_CLOAKING).integer() != 130) {
			status_calc_speed (*sd, AS_CLOAKING, 130, 1);
		}
	}
	else {
		if (sd && sd->get_statusvalue3(SC_CLOAKING).integer() != 103) {
			status_calc_speed (*sd, AS_CLOAKING, 103, 1);
		}
	}

	return end;
}

/*
 *----------------------------------------------------------------------------
 * �X�L�����j�b�g
 *----------------------------------------------------------------------------
 */

/*==========================================
 * ���t/�_���X����߂�
 * flag 1�ō��t���Ȃ瑊���Ƀ��j�b�g��C����
 *
 *------------------------------------------
 */
void skill_stop_dancing(block_list *src, int flag)
{
	struct skill_unit_group* group;
	nullpo_retv(src);

	if( src->has_status(SC_DANCING) )
	{
		group = (struct skill_unit_group *)src->get_statusvalue2(SC_DANCING).pointer(); //�_���X�̃X�L�����j�b�gID��val2�ɓ����Ă�
		if(group && *src == BL_PC)
		{
			if( src->get_statusvalue4(SC_DANCING).integer() )
			{	//���t��?
				map_session_data* dsd = map_session_data::from_blid(src->get_statusvalue4(SC_DANCING).integer()); //������sd�擾
				if(flag && dsd)
				{	//���O�A�E�g�ȂǕЕ��������Ă����t��??�����
					if(src->id == group->src_id)
					{	//�O��?�v�������Ă�PC��������
						group->src_id = src->get_statusvalue4(SC_DANCING).integer(); //�����ɃO��?�v��C����
						if (flag & 1) //���O�A�E�g
							dsd->get_statusvalue4(SC_DANCING) = 0; //�����̑�����0�ɂ��č��t�I�����ʏ�̃_���X?��
						if(flag & 2) //�n�G��тȂ�
							return; //���t���_���X?�Ԃ��I�������Ȃ����X�L�����j�b�g�͒u���Ă��ڂ�
					}
					else if(dsd->block_list::id == group->src_id)
					{	//�������O��?�v�������Ă���PC��������(�����̓O��?�v�������Ă��Ȃ�)
						if (flag & 1) //���O�A�E�g
							dsd->get_statusvalue4(SC_DANCING) = 0; //�����̑�����0�ɂ��č��t�I�����ʏ�̃_���X?��
						if(flag & 2) //�n�G��тȂ�
							return; //���t���_���X?�Ԃ��I�������Ȃ����X�L�����j�b�g�͒u���Ă��ڂ�
					}
					status_change_end(src, SC_DANCING, -1);	//�����̃X�e?�^�X���I��������
					//�����ăO��?�v�͏����Ȃ��������Ȃ��̂ŃX�e?�^�X�v�Z������Ȃ��H
					return;
				}
				else if(dsd)
				{
					if (src->id == group->src_id)	//�O��?�v�������Ă�PC���~�߂�
						status_change_end(dsd, SC_DANCING, -1);	//����̃X�e?�^�X���I��������
					if(dsd->block_list::id == group->src_id)	//�������O��?�v�������Ă���PC���~�߂�(�����̓O��?�v�������Ă��Ȃ�)
						status_change_end(src, SC_DANCING, -1);	//�����̃X�e?�^�X���I��������
				}
			}
			if( (flag & 2) )
			{ //�n�G�Ŕ�񂾂Ƃ��Ƃ��̓��j�b�g�����
				map_session_data *sd = (map_session_data *)src;
				if (sd) skill_unit_move_unit_group(*group, sd->block_list::m, (sd->walktarget.x - sd->block_list::x), (sd->walktarget.y - sd->block_list::y));
				return;
			}
			skill_delunitgroup(*group);
		}
	}
}

/*==========================================
 * �X�L�����j�b�g������
 *------------------------------------------
 */
struct skill_unit *skill_initunit(struct skill_unit_group *group,int idx,int x,int y)
{
	struct skill_unit *unit;

	nullpo_retr(NULL, group);
	nullpo_retr(NULL, unit=&group->unit[idx]);

	if(!unit->alive)
		group->alive_count++;

	unit->register_id();
	unit->block_list::m=group->map;
	unit->block_list::x=x;
	unit->block_list::y=y;
	unit->group=group;
	unit->val1=unit->val2=0;
	unit->alive=1;

	unit->addblock();
	clif_skill_setunit(*unit);

	if (group->skill_id==HP_BASILICA)
		skill_basilica_cell(unit,true);

	return unit;
}

/*==========================================
 * �X�L�����j�b�g�폜
 *------------------------------------------
 */
int skill_delunit(struct skill_unit *unit)
{
	struct skill_unit_group *group;

	nullpo_retr(0, unit);
	if(!unit->alive)
		return 0;
	nullpo_retr(0, group=unit->group);

	// onlimit�C�x���g�Ăяo��
	skill_unit_onlimit( unit,gettick() );

	// onout�C�x���g�Ăяo��
	if (!unit->range)
	{
		maps[unit->block_list::m].foreachincell( CSkillUnitEffect(*unit,gettick(),0),
			unit->block_list::x, unit->block_list::y, BL_ALL);
	}

	if (group->skill_id==HP_BASILICA)
		skill_basilica_cell(unit,false);

	clif_skill_delunit(*unit);

	unit->group=NULL;
	unit->alive=0;
	unit->freeblock();
	if(group->alive_count>0 && (--group->alive_count)<=0)
		skill_delunitgroup(*group);

	return 0;
}
/*==========================================
 * �X�L�����j�b�g�O��?�v������
 *------------------------------------------
 */
static int skill_unit_group_newid = MAX_SKILL_DB;

struct skill_unit_group *skill_initunitgroup(block_list *src,int count,unsigned short skillid,unsigned short skilllv,int unit_id)
{
	int i;
	struct skill_unit_group *group=NULL, *list=NULL;
	int maxsug=0;

	if(skilllv <= 0) return 0;

	nullpo_retr(NULL, src);

	if(*src==BL_PC){
		list=((map_session_data *)src)->skillunit;
		maxsug=MAX_SKILLUNITGROUP;
	}else if(*src==BL_MOB){
		list=((struct mob_data *)src)->skillunit;
		maxsug=MAX_MOBSKILLUNITGROUP;
	}else if(*src==BL_PET){
		list=((struct pet_data *)src)->skillunit;
		maxsug=MAX_MOBSKILLUNITGROUP;
	}
	if(list){
		for(i=0;i<maxsug;++i)	// �󂢂Ă������?��
			if(list[i].group_id==0){
				group=&list[i];
				break;
			}

		if(group==NULL){	// �󂢂ĂȂ��̂ŌÂ�����?��
			int j=0;
			unsigned long maxdiff=0,x,tick=gettick();
			for(i=0;i<maxsug;++i)
				if((x=DIFF_TICK(tick,list[i].tick))>maxdiff){
					maxdiff=x;
					j=i;
				}
			skill_delunitgroup(list[j]);
			group=&list[j];
		}
	}

	if(group==NULL){
		ShowMessage("skill_initunitgroup: error unit group !\n"
					CL_SPACE"error not recoverable, quitting.\n");
		exit(1);
	}

	group->src_id=src->id;
	group->party_id=src->get_party_id();
	group->guild_id=src->get_guild_id();
	group->group_id=skill_unit_group_newid++;
	if(skill_unit_group_newid<=0)
		skill_unit_group_newid = MAX_SKILL_DB;
	
	group->unit= new skill_unit[count];

	group->unit_count=count;
	group->val1=group->val2=0;
	group->skill_id=skillid;
	group->skill_lv=skilllv;
	group->unit_id=unit_id;
	group->map=src->m;
	group->limit=10000;
	group->interval=1000;
	group->tick=gettick();
	if (skillid == PR_SANCTUARY) //Sanctuary starts healing +1500ms after casted. [Skotlex]
		group->tick += 1500;


	if (skill_get_unit_flag(skillid)&UF_DANCE) {
		map_session_data *sd = NULL;
		if(*src==BL_PC && (sd=(map_session_data *)src) ){
			sd->skillid_dance=skillid;
			sd->skilllv_dance=skilllv;
		}
		status_change_start(src,SC_DANCING,skillid,basics::numptr(group),0,0,skill_get_time(skillid,skilllv)+1000,0);
		//���t�X�L���͑������_���X��Ԃɂ���
		if (sd && skill_get_unit_flag(skillid)&UF_ENSEMBLE) {
			int c=0;
			maps[sd->block_list::m].foreachinarea( CSkillCheckConditionUse(*sd,c),
				sd->block_list::x, sd->block_list::y, 1, BL_PC);
		}
	}
	return group;
}

/*==========================================
 * �X�L�����j�b�g�O��?�v�폜
 *------------------------------------------
 */
int skill_delunitgroup(struct skill_unit_group &group)
{

	if( group.unit_count > 0 )
	{
		
		block_list *src=block_list::from_blid(group.src_id);
		//�_���X�X�L���̓_���X��Ԃ���������
		if(src)
		{
			if( skill_get_unit_flag(group.skill_id)&UF_DANCE )
				status_change_end(src,SC_DANCING,-1);
			if( group.unit_id == UNT_MAGIC_SKILLS)
			{
				if( src->has_status(SC_MAGICPOWER) )	//�}�W�b�N�p��?��?�ʏI��
					status_change_end(src,SC_MAGICPOWER,-1);
			}
		}
		group.alive_count=0;
		if( group.unit!=NULL )
		{
			int i;
			for(i=0; i<group.unit_count; ++i)
			{
				if(group.unit[i].alive)
					skill_delunit(&group.unit[i]);
			}
			delete[] group.unit;
			group.unit = NULL;
		}
		group.valstring.clear();
		group.src_id=0;
		group.group_id=0;
		group.unit_count=0;
	}
	return 0;
}

/*==========================================
 * �X�L�����j�b�g�O��?�v�S�폜
 *------------------------------------------
 */
int skill_clear_unitgroup(block_list *src)
{
	struct skill_unit_group *group=NULL;
	int maxsug=0;

	nullpo_retr(0, src);

	if(*src==BL_PC){
		group=((map_session_data *)src)->skillunit;
		maxsug=MAX_SKILLUNITGROUP;
	} else if(*src==BL_MOB){
		group=((struct mob_data *)src)->skillunit;
		maxsug=MAX_MOBSKILLUNITGROUP;
	} else if(*src==BL_PET){ // [Valaris]
		group=((struct pet_data *)src)->skillunit;
		maxsug=MAX_MOBSKILLUNITGROUP;
	} else
		return 0;
	if(group){
		int i;
		for(i=0;i<maxsug;++i)
			if(group[i].group_id>0 && group[i].src_id == src->id)
				skill_delunitgroup(group[i]);
	}
	return 0;
}

/*==========================================
 * �X�L�����j�b�g�O��?�v�̔�e��tick?��
 *------------------------------------------
 */
struct skill_unit_group_tickset *skill_unitgrouptickset_search(block_list *bl,struct skill_unit_group *group,unsigned long tick)
{
	int i,j=-1,k,s;
	unsigned short id;
	struct skill_unit_group_tickset *set;

	nullpo_retr(0, bl);
	if (group->interval==-1)
		return NULL;

	if (*bl == BL_PC)
		set = ((map_session_data *)bl)->skillunittick;
	else if (*bl== BL_MOB)
		set = ((struct mob_data *)bl)->skillunittick;
	else
		return 0;

	if (skill_get_unit_flag(group->skill_id)&UF_NOOVERLAP)
		id = s = group->skill_id;
	else
		id = s = group->group_id;

	for (i=0; i<MAX_SKILLUNITGROUPTICKSET; ++i) {
		k = (i+s) % MAX_SKILLUNITGROUPTICKSET;
		if (set[k].skill_id == id)
			return &set[k];
		else if (j==-1 && (DIFF_TICK(tick,set[k].tick)>0 || set[k].skill_id==0))
			j=k;
	}

	if (j == -1) {
		if(config.error_log) {
			ShowWarning("skill_unitgrouptickset_search: tickset is full\n");
		}
		j = id % MAX_SKILLUNITGROUPTICKSET;
	}

	set[j].skill_id = id;
	set[j].tick = tick;
	return &set[j];
}

/*==========================================
 * �X�L�����j�b�g�^�C�}??��
 *------------------------------------------
 */
int skill_unit_timer(int tid, unsigned long tick, int id, basics::numptr data)
{
	block_list::freeblock_lock();
	block_list::foreachobject( CSkillUnitTimer(tick), BL_SKILL);
	block_list::freeblock_unlock();
	return 0;
}


/*==========================================
 * �X�L�����j�b�g�ړ���?��
 *------------------------------------------
 */
int skill_unit_move(block_list &bl,unsigned long tick,int flag)
{
	if( !bl.is_on_map() )
		return 1;
	if (bl!=BL_PC && bl!=BL_MOB)
		return 0;

	block_list::freeblock_lock();
	maps[bl.m].foreachincell( CSkillUnitMove(bl,tick,flag), bl.x, bl.y, BL_SKILL);
	block_list::freeblock_unlock();
	return 0;
}

/*==========================================
 * �X�L�����j�b�g��?�̈ړ���?��
 * ��?�̓O��?�v�ƈړ���
 *------------------------------------------
 */
int skill_unit_move_unit_group(struct skill_unit_group& group, unsigned short m, int dx,int dy)
{
	int i,j;
	unsigned long tick = gettick();
	int *m_flag;


	if(group.unit_count<=0)
		return 0;
	if(group.unit==NULL)
		return 0;

	// �ړ��\�ȃX�L���̓_���X�n�ƁA�u���X�g�}�C���A�N���C���A�[�g���b�v�̂�
	if (!(skill_get_unit_flag(group.skill_id)&UF_DANCE) &&
			group.skill_id!=HT_CLAYMORETRAP && group.skill_id!=HT_BLASTMINE)
		return 0;
	if (skill_get_unit_flag(group.skill_id)&UF_ENSEMBLE) //Ensemble skills can't be moved!
		return 0;
		
	m_flag = new int[group.unit_count];
	memset(m_flag,0,group.unit_count*sizeof(int));
	// ��Ƀt���O��S�����߂�
	//    m_flag
	//		0: �P���ړ�
	//      1: ���j�b�g���ړ�����(���ʒu���烆�j�b�g���Ȃ��Ȃ�)
	//      2: �c�����V�ʒu���ړ���ƂȂ�(�ړ���Ƀ��j�b�g�����݂��Ȃ�)
	//      3: �c��
	for(i=0;i<group.unit_count;++i)
	{
			struct skill_unit &unit1 = group.unit[i];
	
		if (!unit1.alive || unit1.block_list::m!=m)
			continue;
		for(j=0;j<group.unit_count;++j)
		{
			struct skill_unit &unit2=group.unit[j];
			if (!unit2.alive)
				continue;
			if( unit1.block_list::x+dx==unit2.block_list::x && unit1.block_list::y+dy==unit2.block_list::y )
			{	// �ړ���Ƀ��j�b�g�����Ԃ��Ă���
				m_flag[i] |= 0x1;
			}
			if( unit1.block_list::x-dx==unit2.block_list::x && unit1.block_list::y-dy==unit2.block_list::y )
			{	// ���j�b�g�����̏ꏊ�ɂ���Ă���
				m_flag[i] |= 0x2;
			}
		}
	}
	// �t���O�Ɋ�Â��ă��j�b�g�ړ�
	// �t���O��1��unit��T���A�t���O��2��unit�̈ړ���Ɉڂ�
	j = 0;
	for (i=0;i<group.unit_count;++i)
	{
		struct skill_unit &unit1 = group.unit[i];
		if( !unit1.alive )
			continue;
		if( !(m_flag[i]&0x2) )
		{	// ���j�b�g���Ȃ��Ȃ�ꏊ�ŃX�L�����j�b�g�e��������
			maps[unit1.block_list::m].foreachincell( CSkillUnitEffect( unit1, tick, 0),
				unit1.block_list::x, unit1.block_list::y, BL_ALL);
		}
		if( m_flag[i]==0 )
		{
			// �P���ړ�
			unit1.delblock();
			unit1.block_list::m = m;
			unit1.block_list::x += dx;
			unit1.block_list::y += dy;
			unit1.addblock();
			clif_skill_setunit(unit1);
		}
		else if( m_flag[i]==1 )
		{	// �t���O��2�̂��̂�T���Ă��̃��j�b�g�̈ړ���Ɉړ�
			for( ;j<group.unit_count; ++j)
			{
				if (m_flag[j]==2)
				{	// �p���ړ�
					struct skill_unit &unit2 = group.unit[j];
					if (!unit2.alive)
						continue;
					unit1.delblock();
					unit1.block_list::m = m;
					unit1.block_list::x = unit2.block_list::x+dx;
					unit1.block_list::y = unit2.block_list::y+dy;
					unit1.addblock();
					clif_skill_setunit(unit1);
					++j;
					break;
				}
			}
		}
		if (!(m_flag[i]&0x2))
		{	// �ړ���̏ꏊ�ŃX�L�����j�b�g�𔭓�
			maps[unit1.block_list::m].foreachincell( CSkillUnitEffect(unit1, tick, 1),
				unit1.block_list::x, unit1.block_list::y, BL_ALL);
		}
	}
	delete[] m_flag;
	return 0;
}

/*----------------------------------------------------------------------------
 * �A�C�e������
 *----------------------------------------------------------------------------
 */

/*==========================================
 * �A�C�e�������\����
 *------------------------------------------
 */
int skill_can_produce_mix( map_session_data &sd, unsigned short nameid, int trigger )
{
	int i,j;

	if(nameid<=0)
		return 0;

	for(i=0;i<MAX_SKILL_PRODUCE_DB;++i){
		if(skill_produce_db[i].nameid == nameid )
			break;
	}
	if( i >= MAX_SKILL_PRODUCE_DB )	// �f?�^�x?�X�ɂȂ�
		return 0;

	if(trigger>=0){
		if(trigger == 32 || trigger == 16 || trigger==64 || trigger == 256) {
			if(skill_produce_db[i].itemlv!=trigger)	// �t�@?�}�V?���|?�V�����ނƗn??��?�ΈȊO�͂���
				return 0;
		}else{
			if(skill_produce_db[i].itemlv>=16)		// ����ȊO�͂���
				return 0;
			if( itemdb_wlv(nameid)>trigger )	// ����Lv����
				return 0;
		}
	}
	if( (j=skill_produce_db[i].req_skill)>0 && sd.skill_check(j)<=0 )
		return 0;		// �X�L��������Ȃ�

	for(j=0;j<MAX_PRODUCE_RESOURCE;++j){
		int id,x,y;
		if( (id=skill_produce_db[i].mat_id[j]) <= 0 )	// ����ȏ�͍ޗ��v��Ȃ�
			continue;
		if(skill_produce_db[i].mat_amount[j] <= 0) {
			if(pc_search_inventory(sd,id) < 0)
				return 0;
		}
		else {
			for(y=0,x=0;y<MAX_INVENTORY;++y)
				if( sd.status.inventory[y].nameid == id )
					x+=sd.status.inventory[y].amount;
			if(x<skill_produce_db[i].mat_amount[j]) // �A�C�e��������Ȃ� 
				return 0;
		}
	}
	return i+1;
}

/*==========================================
 * �A�C�e�������\����
 *------------------------------------------
 */
int skill_produce_mix(map_session_data &sd, unsigned short nameid, unsigned short slot1, unsigned short slot2, unsigned short slot3)
{
	unsigned short slot[3];
	int i,sc,ele,equip,make_per,flag;
	int wlv=0;
	//Calculate Common Class and Baby/High/Common flags
	struct pc_base_job s_class = pc_calc_base_job(sd.status.class_);
	int idx=skill_can_produce_mix(sd,nameid,-1);

	if( !idx || !sd.state.produce_flag )	// ?���s��
		return 0;

	sd.state.produce_flag=0;

	idx--;
	slot[0]=slot1;
	slot[1]=slot2;
	slot[2]=slot3;

	// ����?��?��
	for(i=0,sc=0,ele=0;i<3;++i){
		int j;
		if( slot[i]<=0 )
			continue;
		j = pc_search_inventory(sd,slot[i]);
		if(j < 0)	// �s���p�P�b�g(�A�C�e������)�`�F�b�N
			continue;
		if(slot[i]==1000){	// Star Crumb
			pc_delitem(sd,j,1,1);
			++sc;
		}
		if(slot[i]>=994 && slot[i]<=997 && ele==0){	// Flame Heart . . . Great Nature
			static const int ele_table[4]={3,1,4,2};
			pc_delitem(sd,j,1,1);
			ele=ele_table[slot[i]-994];
		}
	}

	// �ޗ�����
	for(i=0;i<MAX_PRODUCE_RESOURCE;++i){
		int j,id,x;
		if( (id=skill_produce_db[idx].mat_id[i]) <= 0 )
			continue;
		x=skill_produce_db[idx].mat_amount[i];	// �K�v�Ȍ�?
		do{	// �Q�ȏ�̃C���f�b�N�X�ɂ܂������Ă��邩������Ȃ�
			int y=0;
			j = pc_search_inventory(sd,id);

			if(j >= 0){
				y = sd.status.inventory[j].amount;
				if(y>x)y=x;	// ����Ă���
				pc_delitem(sd,j,y,0);
			}else {
				if(config.error_log)
					ShowMessage("skill_produce_mix: material item error\n");
			}

			x-=y;	// �܂�����Ȃ���?���v�Z
		}while( j>=0 && x>0 );	// �ޗ�������邩�A�G��?�ɂȂ�܂ŌJ��Ԃ�
	}

	// �m������
	if((equip=itemdb_isSingleStorage(nameid)))
		wlv = itemdb_wlv(nameid);
	if(!equip) {
// Corrected rates [DracoRPG] --------------------------//
		if(skill_produce_db[idx].req_skill==AM_PHARMACY) {
			make_per = sd.skill_check(AM_LEARNINGPOTION)*100
				+ sd.skill_check(AM_PHARMACY)*300 + sd.status.job_level*20
				+ sd.paramc[3]*5 + sd.paramc[4]*10+sd.paramc[5]*10;

			if(nameid >= 501 && nameid <= 505) // Normal potions
				make_per += 2000 + sd.skill_check(AM_POTIONPITCHER)*100;
			else if(nameid >= 605 && nameid <= 606) // Anodyne & Aloevera (not sure of the formula, I put the same base value as normal pots but without the Aid Potion bonus since they are not throwable pots ^^)
				make_per += 2000;
//			else if(nameid >= 545 && nameid <= 547) // Concentrated potions
			else if(nameid == 970) // Alcohol
				make_per += 1000;
			else if(nameid == 7135) // Bottle Grenade
				make_per += 500 + sd.skill_check(AM_DEMONSTRATION)*100;
			else if(nameid == 7136) // Acid Bottle
				make_per += 500 + sd.skill_check(AM_ACIDTERROR)*100;
			else if(nameid == 7137) // Plant Bottle
				make_per += 500 + sd.skill_check(AM_CANNIBALIZE)*100;
			else if(nameid == 7138) // Marine Sphere Bottle
				make_per += 500 + sd.skill_check(AM_SPHEREMINE)*100;
			else if(nameid == 7139) // Glistening Coat
				make_per += 500 + sd.skill_check(AM_CP_WEAPON)*100 + sd.skill_check(AM_CP_SHIELD)*100 +
					sd.skill_check(AM_CP_ARMOR)*100 + sd.skill_check(AM_CP_HELM)*100;
		} else if (skill_produce_db[idx].req_skill == ASC_CDP) {
			make_per = 2000 + 40*sd.paramc[4] + 20*sd.paramc[5]; // Poison Bottle
		} else { //Refining ores - using JRO data [Skotlex]
			int skill = sd.skill_check(skill_produce_db[idx].req_skill);
			make_per = 2000 + sd.status.job_level*20 + sd.paramc[4]*10 + sd.paramc[5]*10; //Base chance
			if(nameid == 998) //Iron
				make_per += 200+skill*600; //Bonus: +26/+32/+38/+44/+50
			else if(nameid == 999) //Steel
				make_per += 100+skill*500; //Bonus: +15/+20/+25/+30/+35
			else if(nameid==1000) //Star Crumb
				make_per = 20000; //Star Crumbs are 100% success crafting rate? (made 200% so it succeeds even after penalties) [Skotlex]
			else	//Enchanted Stones
				make_per += -500 +skill*500; //Bonus: - 5/+ 0/+ 5/+10/+15

		}
		if(config.pp_rate != 100)
			make_per = make_per * config.pp_rate / 100;

	} else { // Weapon Forging. Using rates based on jRO [Skotlex]
		make_per = 2000 + sd.status.job_level*20 + sd.get_dex()*10 + sd.get_luk()*10; //Base
		make_per += 2500 + sd.skill_check(skill_produce_db[idx].req_skill)*500; //Skill bonus: +30/+35/+40
		make_per += sd.skill_check(BS_WEAPONRESEARCH)*100 +((wlv >= 3)? sd.skill_check(BS_ORIDEOCON)*100:0); //Weapon/Oridecon research
		make_per -= (ele?2000:0 + sc*1500 + wlv>1?wlv*1000:0); //Ele: -20%, StarCrumb: -15%ea, Wlevel: -0/-20/-30
		if(pc_search_inventory(sd,989) > 0) make_per+= 1000; //Emperium Anvil +10%
		else if(pc_search_inventory(sd,988) > 0) make_per+= 500; //Gold Anvil +5%
		else if(pc_search_inventory(sd,987) > 0) make_per+= 300; //Oridecon Anvil +3%
		else if(pc_search_inventory(sd,986) > 0) make_per+= 0; //Iron Anvil +0%?

		if(config.wp_rate != 100)	// �m���␳
			make_per = make_per * config.wp_rate / 100;
	}
// - Baby Class Penalty = 80% (from adult's chance) ----//
	if (s_class.upper==2) //if it's a Baby Class
		make_per = (make_per * 80) / 100; //Lupus
// -----------------------------------------------------//

	if(make_per < 1) make_per = 1;

//	if(config.etc_log)
//		ShowMessage("make rate = %d\n",make_per);

	if(rand()%10000 < make_per)
	{	// ����
		struct item tmp_item(nameid);
		if(equip)
		{	// ����̏ꍇ
			tmp_item.card[0]=0x00ff; // ��������t���O 
			tmp_item.card[1]=((sc*5)<<8)+ele;	// ?���Ƃ悳
			tmp_item.card[2]=basics::GetWord(sd.status.char_id,0);	// �L����ID
			tmp_item.card[3]=basics::GetWord(sd.status.char_id,1);
		}
		else if((config.produce_item_name_input && skill_produce_db[idx].req_skill!=AM_PHARMACY) ||
			(config.produce_potion_name_input && skill_produce_db[idx].req_skill==AM_PHARMACY))
		{
			tmp_item.card[0]=0x00fe;
			tmp_item.card[1]=0;
			tmp_item.card[2]=basics::GetWord(sd.status.char_id,0);	// �L����ID
			tmp_item.card[3]=basics::GetWord(sd.status.char_id,1);
		}

		if(log_config.produce > 0)
			log_produce(sd,nameid,slot1,slot2,slot3,1);

		switch (skill_produce_db[idx].req_skill)
		{
			case AM_PHARMACY:
				clif_produceeffect(sd,nameid,2);// ��?�G�t�F�N�g 
			clif_misceffect(sd,5); // ���l�ɂ�������ʒm 
			if(nameid >= 545 && nameid <= 547)
			{	// Fame point system [DracoRPG]
		  		sd.potion_success_counter++;
		  		if(sd.potion_success_counter == 3) {
					chrif_updatefame(sd, FAME_CHEM, 1); // Success to prepare 3 Concentrated Potions in a row = +1 fame point
		  		}
				if(sd.potion_success_counter == 5) {
					chrif_updatefame(sd, FAME_CHEM, 3); // Success to prepare 5 Concentrated Potions in a row = +3 fame point
				}
		  		if(sd.potion_success_counter == 7) {
					chrif_updatefame(sd, FAME_CHEM, 10); // Success to prepare 7 Concentrated Potions in a row = +10 fame point
	  			}
				if(sd.potion_success_counter == 10) {
					chrif_updatefame(sd, FAME_CHEM, 50);	// Success to prepare 10 Concentrated Potions in a row = +50 fame point
					sd.potion_success_counter = 0;
				}
			}
			else 
				sd.potion_success_counter = 0;
				break;
			case ASC_CDP:
				clif_produceeffect(sd,nameid,2);// �b��Ő�?�G�t�F�N�g 
				clif_misceffect(sd,5);
				break;
			default:  // ���퐻���A�R�C������ 
				clif_produceeffect(sd,nameid,0); // ���퐻���G�t�F�N�g 
				clif_misceffect(sd,3);
				if(equip && itemdb_wlv(nameid) >= 3 && ((ele? 1 : 0) + sc) >= 3)
					chrif_updatefame(sd, FAME_SMITH, 10); // Success to forge a lv3 weapon with 3 additional ingredients = +10 fame point
				break;
		}

		if((flag = pc_additem(sd,tmp_item,1)))
		{
			clif_additem(sd,0,0,flag);
			flooritem_data::create(tmp_item,1,sd.block_list::m,sd.block_list::x,sd.block_list::y,NULL,NULL,NULL,0);
		}
	}
	else
	{
		if(log_config.produce > 0)
			log_produce(sd,nameid,slot1,slot2,slot3,0);

		switch (skill_produce_db[idx].req_skill) {
			case AM_PHARMACY:
				clif_produceeffect(sd,nameid,3);// ��?���s�G�t�F�N�g 
				clif_misceffect(sd,6); // ���l�ɂ����s��ʒm 
				sd.potion_success_counter = 0; // Fame point system [DracoRPG]
				break;
			case ASC_CDP:
				clif_produceeffect(sd,nameid,3); // �b��Ő�?�G�t�F�N�g 
				clif_misceffect(sd,6); // ���l�ɂ����s��ʒm 
				sd.heal(-(sd.status.max_hp>>2), 0);
				break;
			default:
				clif_produceeffect(sd,nameid,1);// ���퐻�����s�G�t�F�N�g 
				clif_misceffect(sd,2); // ���l�ɂ����s��ʒm 
				break;
		}
	}
	return 0;
}

int skill_arrow_create( map_session_data *sd,unsigned short nameid)
{
	int i,j,flag,index=-1;
	struct item tmp_item;

	nullpo_retr(0, sd);

	if(nameid <= 0 || sd->state.produce_flag==0)
		return 1;

	sd->state.produce_flag = 0;

	for(i=0;i<MAX_SKILL_ARROW_DB;++i)
	{
		if(nameid == skill_arrow_db[i].nameid)
		{
			index = i;
			break;
		}
	}
	if(index < 0 || (j = pc_search_inventory(*sd,nameid)) < 0)
		return 1;

	pc_delitem(*sd,j,1,0);
	for(i=0;i<5;++i)
	{
		tmp_item = (struct item)(skill_arrow_db[index].cre_id[i]);
		tmp_item.amount = skill_arrow_db[index].cre_amount[i];
		if(config.making_arrow_name_input)
		{
			tmp_item.card[0]=0x00fe;
			tmp_item.card[1]=0;
			tmp_item.card[2]=basics::GetWord(sd->status.char_id,0);	// �L����ID
			tmp_item.card[3]=basics::GetWord(sd->status.char_id,1);
		}
		if(tmp_item.nameid <= 0 || tmp_item.amount <= 0)
			continue;
		if((flag = pc_additem(*sd,tmp_item,tmp_item.amount)))
		{
			clif_additem(*sd,0,0,flag);
			flooritem_data::create(tmp_item,tmp_item.amount,sd->block_list::m,sd->block_list::x,sd->block_list::y,NULL,NULL,NULL,0);
		}
	}

	return 0;
}

/*----------------------------------------------------------------------------
 * �������n
 */

/*----------------------------------------------------------------------------
 * �������n
 */

/*
 * �����񏈗�
 *        ',' �ŋ�؂��� val �ɖ߂�
 */
int skill_split_str(char *str,char **val,int num)
{
	int i;

	for (i=0; i<num && str; ++i){
		val[i] = str;
		str = strchr(str,',');
		if (str)
			*str++=0;
	}
	return i;
}
/*
 * �����񏈗�
 *      ':' �ŋ�؂���atoi����val�ɖ߂�
 */
int skill_split_atoi(char *str,int *val)
{
	size_t i;
	int max=INT_MIN;
	for (i=0; i<MAX_SKILL_LEVEL; ++i)
	{
		if(str)
		{
			val[i] = atoi(str);
			if(max<val[i]) max = val[i];
			str = strchr(str,':');
			if(str)
				*str++=0;
		}
		else
		{
			val[i] = max;
		}
	}
	return i;
}

/*
 * �X�L�����j�b�g�̔z�u���쐬
 */
void skill_init_unit_layout()
{
	int i,j,size,pos = 0;

	memset(skill_unit_layout,0,sizeof(skill_unit_layout));
	// ��`�̃��j�b�g�z�u���쐬����
	for (i=0; i<=MAX_SQUARE_LAYOUT; ++i) {
		size = i*2+1;
		skill_unit_layout[i].count = size*size;
		for (j=0; j<size*size; ++j) {
			skill_unit_layout[i].dx[j] = (j%size-i);
			skill_unit_layout[i].dy[j] = (j/size-i);
		}
	}
	pos = i;
	// ��`�ȊO�̃��j�b�g�z�u���쐬����
	for (i=0;i<MAX_SKILL_DB;++i) {
		if (!skill_db[i].unit_id[0] || skill_db[i].unit_layout_type[0] != -1)
			continue;
		switch (i) {
			case MG_FIREWALL:
			case WZ_ICEWALL:
				// �t�@�C�A�[�E�H�[���A�A�C�X�E�H�[���͕����ŕς��̂ŕʏ���
				break;
			case PR_SANCTUARY:
			{
				static const int dx[] = {
					-1, 0, 1,-2,-1, 0, 1, 2,-2,-1,
					 0, 1, 2,-2,-1, 0, 1, 2,-1, 0, 1};
				static const int dy[]={
					-2,-2,-2,-1,-1,-1,-1,-1, 0, 0,
					 0, 0, 0, 1, 1, 1, 1, 1, 2, 2, 2};
				skill_unit_layout[pos].count = 21;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case PR_MAGNUS:
			{
				static const int dx[] = {
					-1, 0, 1,-1, 0, 1,-3,-2,-1, 0,
					 1, 2, 3,-3,-2,-1, 0, 1, 2, 3,
					-3,-2,-1, 0, 1, 2, 3,-1, 0, 1,-1, 0, 1};
				static const int dy[] = {
					-3,-3,-3,-2,-2,-2,-1,-1,-1,-1,
					-1,-1,-1, 0, 0, 0, 0, 0, 0, 0,
					 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3};
				skill_unit_layout[pos].count = 33;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case AS_VENOMDUST:
			{
				static const int dx[] = {-1, 0, 0, 0, 1};
				static const int dy[] = { 0,-1, 0, 1, 0};
				skill_unit_layout[pos].count = 5;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case CR_GRANDCROSS:
			case NPC_GRANDDARKNESS:
			{
				static const int dx[] = {
					 0, 0,-1, 0, 1,-2,-1, 0, 1, 2,
					-4,-3,-2,-1, 0, 1, 2, 3, 4,-2,
					-1, 0, 1, 2,-1, 0, 1, 0, 0};
				static const int dy[] = {
					-4,-3,-2,-2,-2,-1,-1,-1,-1,-1,
					 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
					 1, 1, 1, 1, 2, 2, 2, 3, 4};
				skill_unit_layout[pos].count = 29;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case PF_FOGWALL:
			{
				static const int dx[] = {
					-2,-1, 0, 1, 2,-2,-1, 0, 1, 2,-2,-1, 0, 1, 2};
				static const int dy[] = {
					-1,-1,-1,-1,-1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
				skill_unit_layout[pos].count = 15;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			case PA_GOSPEL:
			{
				static const int dx[] = {
					-1, 0, 1,-1, 0, 1,-3,-2,-1, 0,
					 1, 2, 3,-3,-2,-1, 0, 1, 2, 3,
					-3,-2,-1, 0, 1, 2, 3,-1, 0, 1,
					-1, 0, 1};
				static const int dy[] = {
					-3,-3,-3,-2,-2,-2,-1,-1,-1,-1,
					-1,-1,-1, 0, 0, 0, 0, 0, 0, 0,
					 1, 1, 1, 1, 1, 1, 1, 2, 2, 2,
					 3, 3, 3};
				skill_unit_layout[pos].count = 33;
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
				break;
			}
			default:
				ShowMessage("unknown unit layout at skill %d\n",i);
				break;
		}
		if (!skill_unit_layout[pos].count)
			continue;
		for (j=0;j<MAX_SKILL_LEVEL;++j)
			skill_db[i].unit_layout_type[j] = pos;
		pos++;
	}

	// �t�@�C���[�E�H�[��
	firewall_unit_pos = pos;
	for (i=0;i<8;++i) {
		if (i&1) {	// �΂ߔz�u
			skill_unit_layout[pos].count = 5;
			if (i&0x2) {
				int dx[] = {-1,-1, 0, 0, 1};
				int dy[] = { 1, 0, 0,-1,-1};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {
				int dx[] = { 1, 1 ,0, 0,-1}; 
				int dy[] = { 1, 0, 0,-1,-1}; 
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		} else {	// �c���z�u
			skill_unit_layout[pos].count = 3;
			if (i%4==0) {	// �㉺
				int dx[] = {-1, 0, 1};
				int dy[] = { 0, 0, 0};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {			// ���E
				int dx[] = { 0, 0, 0};
				int dy[] = {-1, 0, 1};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		}
		pos++;
	}
	// �A�C�X�E�H�[��
	icewall_unit_pos = pos;
	for (i=0;i<8;++i) {
		skill_unit_layout[pos].count = 5;
		if (i&1) {	// �΂ߔz�u
			if (i&0x2) {
				int dx[] = {-2,-1, 0, 1, 2};
				int dy[] = { 2,-1, 0,-1,-2};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {
				int dx[] = { 2, 1 ,0,-1,-2}; 
				int dy[] = { 2, 1, 0,-1,-2}; 
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		} else {	// �c���z�u
			if (i%4==0) {	// �㉺
				int dx[] = {-2,-1, 0, 1, 2};
				int dy[] = { 0, 0, 0, 0, 0};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			} else {			// ���E
				int dx[] = { 0, 0, 0, 0, 0};
				int dy[] = {-2,-1, 0, 1, 2};
				memcpy(skill_unit_layout[pos].dx,dx,sizeof(dx));
				memcpy(skill_unit_layout[pos].dy,dy,sizeof(dy));
			}
		}
		pos++;
	}
}

/*==========================================
 * �X�L��?�W�t�@�C��?��?��
 * skill_db.txt �X�L���f?�^
 * skill_cast_db.txt �X�L���̉r�����Ԃƃf�B���C�f?�^
 * produce_db.txt �A�C�e���쐬�X�L���p�f?�^
 * create_arrow_db.txt ��쐬�X�L���p�f?�^
 * abra_db.txt �A�u���J�_�u��?���X�L���f?�^
 *------------------------------------------
 */
int skill_readdb(void)
{
	int i,j,k,l,m;
	FILE *fp;
	char *p, line[1024];
	char *filename[]={"db/produce_db.txt","db/produce_db2.txt"};

	// �X�L���f?�^�x?�X
	memset(skill_db,0,sizeof(skill_db));
	fp=basics::safefopen("db/skill_db.txt","r");
	if(fp==NULL){
		ShowError("can't read %s\n","db/skill_db.txt");
		return 1;
	}
	while(fgets(line,sizeof(line),fp)){
		char *split[50];
		if( !is_valid_line(line) )
			continue;
		j = skill_split_str(line,split,14);
		if(j < 14 || split[13]==NULL)
			continue;

		i=atoi(split[0]);
		if (i>=10000 && i<10015) // for guild skills [Celest]
			i -= 9500;
		else if(i<=0 || i>MAX_SKILL_DB)
			continue;

// 	ShowMessage("skill id=%d\n",i);
		skill_split_atoi(split[1],skill_db[i].range);
		skill_db[i].hit=atoi(split[2]);
		skill_db[i].inf=atoi(split[3]);
		skill_db[i].pl=atoi(split[4]);
		skill_db[i].nk=atoi(split[5]);
		skill_db[i].max=atoi(split[6]);
		skill_split_atoi(split[7],skill_db[i].num);

		if(strcasecmp(split[8],"yes") == 0)
			skill_db[i].castcancel=1;
		else
			skill_db[i].castcancel=0;
		skill_db[i].cast_def_rate=atoi(split[9]);
		skill_db[i].inf2=atoi(split[10]);
		skill_db[i].maxcount=atoi(split[11]);
		if(strcasecmp(split[12],"weapon") == 0)
			skill_db[i].skill_type=BF_WEAPON;
		else if(strcasecmp(split[12],"magic") == 0)
			skill_db[i].skill_type=BF_MAGIC;
		else if(strcasecmp(split[12],"misc") == 0)
			skill_db[i].skill_type=BF_MISC;
		else
			skill_db[i].skill_type=0;
		skill_split_atoi(split[13],skill_db[i].blewcount);

		for (j = 0; skill_names[j].id != 0; ++j)
		{
			if (skill_names[j].id == i)
			{
				skill_db[i].name = skill_names[j].name;
				skill_db[i].desc = skill_names[j].desc;
				break;
			}
		}
	}
	fclose(fp);
	ShowStatus("Done reading '"CL_WHITE"%s"CL_RESET"'.\n","db/skill_db.txt");

	fp=basics::safefopen("db/skill_require_db.txt","r");
	if(fp==NULL){
		ShowError("can't read %s\n","db/skill_require_db.txt");
		return 1;
	}
	while(fgets(line,sizeof(line),fp)){
		char *split[50];
		if( !is_valid_line(line) )
			continue;
		j = skill_split_str(line,split,30);
		if(j < 30 || split[29]==NULL)
			continue;

		i=atoi(split[0]);
		if (i>=10000 && i<10015) // for guild skills [Celest]
			i -= 9500;
		else if(i<=0 || i>MAX_SKILL_DB)
			continue;

		skill_split_atoi(split[1],skill_db[i].hp);
		skill_split_atoi(split[2],skill_db[i].mhp);
		skill_split_atoi(split[3],skill_db[i].sp);
		skill_split_atoi(split[4],skill_db[i].hp_rate);
		skill_split_atoi(split[5],skill_db[i].sp_rate);
		skill_split_atoi(split[6],skill_db[i].zeny);
		
		p = split[7];
		for(j=0;j<32;++j){
			l = atoi(p);
			if (l==99) {
				skill_db[i].weapon = 0xffffffff;
				break;
			}
			else
				skill_db[i].weapon |= 1<<l;
			p=strchr(p,':');
			if(!p)
				break;
			++p;
		}

		if( strcasecmp(split[8],"hiding")==0 ) skill_db[i].state=ST_HIDING;
		else if( strcasecmp(split[8],"cloaking")==0 ) skill_db[i].state=ST_CLOAKING;
		else if( strcasecmp(split[8],"hidden")==0 ) skill_db[i].state=ST_HIDDEN;
		else if( strcasecmp(split[8],"riding")==0 ) skill_db[i].state=ST_RIDING;
		else if( strcasecmp(split[8],"falcon")==0 ) skill_db[i].state=ST_FALCON;
		else if( strcasecmp(split[8],"cart")==0 ) skill_db[i].state=ST_CART;
		else if( strcasecmp(split[8],"shield")==0 ) skill_db[i].state=ST_SHIELD;
		else if( strcasecmp(split[8],"sight")==0 ) skill_db[i].state=ST_SIGHT;
		else if( strcasecmp(split[8],"explosionspirits")==0 ) skill_db[i].state=ST_EXPLOSIONSPIRITS;
		else if( strcasecmp(split[8],"recover_weight_rate")==0 ) skill_db[i].state=ST_RECOV_WEIGHT_RATE;
		else if( strcasecmp(split[8],"move_enable")==0 ) skill_db[i].state=ST_MOVE_ENABLE;
		else if( strcasecmp(split[8],"water")==0 ) skill_db[i].state=ST_WATER;
		else skill_db[i].state=ST_NONE;

		skill_split_atoi(split[9],skill_db[i].spiritball);
		skill_db[i].itemid[0]=atoi(split[10]);
		skill_db[i].amount[0]=atoi(split[11]);
		skill_db[i].itemid[1]=atoi(split[12]);
		skill_db[i].amount[1]=atoi(split[13]);
		skill_db[i].itemid[2]=atoi(split[14]);
		skill_db[i].amount[2]=atoi(split[15]);
		skill_db[i].itemid[3]=atoi(split[16]);
		skill_db[i].amount[3]=atoi(split[17]);
		skill_db[i].itemid[4]=atoi(split[18]);
		skill_db[i].amount[4]=atoi(split[19]);
		skill_db[i].itemid[5]=atoi(split[20]);
		skill_db[i].amount[5]=atoi(split[21]);
		skill_db[i].itemid[6]=atoi(split[22]);
		skill_db[i].amount[6]=atoi(split[23]);
		skill_db[i].itemid[7]=atoi(split[24]);
		skill_db[i].amount[7]=atoi(split[25]);
		skill_db[i].itemid[8]=atoi(split[26]);
		skill_db[i].amount[8]=atoi(split[27]);
		skill_db[i].itemid[9]=atoi(split[28]);
		skill_db[i].amount[9]=atoi(split[29]);
	}
	fclose(fp);
	ShowStatus("Done reading '"CL_WHITE"%s"CL_RESET"'.\n","db/skill_require_db.txt");

	// �L���X�e�B���O�f?�^�x?�X
	fp=basics::safefopen("db/skill_cast_db.txt","r");
	if(fp==NULL){
		ShowError("can't read %s\n","db/skill_cast_db.txt");
		return 1;
	}
	while(fgets(line,sizeof(line),fp)){
		char *split[50];
		memset(split,0,sizeof(split));	// [Valaris] thanks to fov
		if( !is_valid_line(line) )
			continue;
		j = skill_split_str(line,split,5);
		if(split[4]==NULL || j<5)
			continue;

		i=atoi(split[0]);
		if (i>=10000 && i<10015) // for guild skills [Celest]
			i -= 9500;
		else if(i<=0 || i>MAX_SKILL_DB)
			continue;

		skill_split_atoi(split[1],skill_db[i].cast);
		skill_split_atoi(split[2],skill_db[i].delay);
		skill_split_atoi(split[3],skill_db[i].upkeep_time);
		skill_split_atoi(split[4],skill_db[i].upkeep_time2);
	}
	fclose(fp);
	ShowStatus("Done reading '"CL_WHITE"%s"CL_RESET"'.\n","db/skill_cast_db.txt");


	// �X�L�����j�b�g�f�[�^�x�[�X
	fp = basics::safefopen("db/skill_unit_db.txt","r");
	if (fp==NULL) {
		ShowError("can't read db/skill_unit_db.txt\n");
		return 1;
	}
        k = 0;
	while (fgets(line,sizeof(line),fp)) {
		char *split[50];
		if( !is_valid_line(line) )
			continue;
		j = skill_split_str(line,split,8);
		if (split[7]==NULL || j<8)
			continue;

		i=atoi(split[0]);
		if (i>=10000 && i<10015) // for guild skills [Celest]
			i -= 9500;
		else if(i<=0 || i>MAX_SKILL_DB)
			continue;
		skill_db[i].unit_id[0] = strtol(split[1],NULL,16);
		skill_db[i].unit_id[1] = strtol(split[2],NULL,16);

		skill_split_atoi(split[3],skill_db[i].unit_layout_type);
		
		skill_db[i].unit_range = atoi(split[4]);
		skill_db[i].unit_interval = atoi(split[5]);

		if( strcasecmp(split[6],"noenemy")==0 ) skill_db[i].unit_target=BCT_NOENEMY;
		else if( strcasecmp(split[6],"friend")==0 ) skill_db[i].unit_target=BCT_NOENEMY;
		else if( strcasecmp(split[6],"party")==0 ) skill_db[i].unit_target=BCT_PARTY;
		else if( strcasecmp(split[6],"all")==0 ) skill_db[i].unit_target=BCT_ALL;
		else if( strcasecmp(split[6],"enemy")==0 ) skill_db[i].unit_target=BCT_ENEMY;
		else if( strcasecmp(split[6],"ally")==0 ) skill_db[i].unit_target=BCT_PARTY|BCT_GUILD;
		else if( strcasecmp(split[6],"self")==0 ) skill_db[i].unit_target=BCT_SELF;
		else skill_db[i].unit_target = strtol(split[6],NULL,16);

		skill_db[i].unit_flag = strtol(split[7],NULL,16);
		++k;
	}
	fclose(fp);
	ShowStatus("Done reading '"CL_WHITE"%s"CL_RESET"'.\n","db/skill_cast_db.txt");
	skill_init_unit_layout();

	// �����n�X�L���f?�^�x?�X
	memset(skill_produce_db,0,sizeof(skill_produce_db));
	for(m=0;m<2;++m){
		fp=basics::safefopen(filename[m],"r");
		if(fp==NULL){
			if(m>0)
				continue;
			ShowError("can't read %s\n",filename[m]);
			return 1;
		}
		k=0;
		while(fgets(line,sizeof(line),fp)){
			char *split[6 + MAX_PRODUCE_RESOURCE * 2];
			int x,y;
			if( !is_valid_line(line) )
				continue;
			memset(split,0,sizeof(split));
			j = skill_split_str(line,split,(3 + MAX_PRODUCE_RESOURCE * 2));
			if(split[0]==0) //fixed by Lupus
				continue;
			i=atoi(split[0]);
			if(i<=0) continue;

			skill_produce_db[k].nameid=i;
			skill_produce_db[k].itemlv=atoi(split[1]);
			skill_produce_db[k].req_skill=atoi(split[2]);

			for(x=3,y=0; split[x] && split[x+1] && y<MAX_PRODUCE_RESOURCE; x+=2,++y){
				skill_produce_db[k].mat_id[y]=atoi(split[x]);
				skill_produce_db[k].mat_amount[y]=atoi(split[x+1]);
			}
			++k;
			if(k >= MAX_SKILL_PRODUCE_DB)
				break;
		}
		fclose(fp);
		ShowStatus("Done reading '"CL_WHITE"%d"CL_RESET"' entries in '"CL_WHITE"%s"CL_RESET"'.\n",k,filename[m]);
	}

	memset(skill_arrow_db,0,sizeof(skill_arrow_db));

	fp=basics::safefopen("db/create_arrow_db.txt","r");
	if(fp==NULL){
		ShowError("can't read %s\n","db/create_arrow_db.txt");
		return 1;
	}
	k=0;
	while(fgets(line,sizeof(line),fp)){
		char *split[16];
		int x,y;
		if( !is_valid_line(line) )
			continue;
		memset(split,0,sizeof(split));
		j = skill_split_str(line,split,13);
		if(split[0]==0) //fixed by Lupus
			continue;
		i=atoi(split[0]);
		if(i<=0)
			continue;

		skill_arrow_db[k].nameid=i;

		for(x=1,y=0;split[x] && split[x+1] && y<5;x+=2,++y){
			skill_arrow_db[k].cre_id[y]=atoi(split[x]);
			skill_arrow_db[k].cre_amount[y]=atoi(split[x+1]);
		}
		++k;
		if(k >= MAX_SKILL_ARROW_DB)
			break;
	}
	fclose(fp);
	ShowStatus("Done reading '"CL_WHITE"%d"CL_RESET"' entries in '"CL_WHITE"%s"CL_RESET"'.\n",k,"db/create_arrow_db.txt");

	memset(skill_abra_db,0,sizeof(skill_abra_db));
	fp=basics::safefopen("db/abra_db.txt","r");
	if(fp==NULL){
		ShowError("can't read %s\n","db/abra_db.txt");
		return 1;
	}
	k=0;
	while(fgets(line,sizeof(line),fp)){
		char *split[16];
		if( !is_valid_line(line) )
			continue;
		memset(split,0,sizeof(split));
		j = skill_split_str(line,split,13);
		if(split[0]==0) //fixed by Lupus
			continue;
		i=atoi(split[0]);
		if(i<=0)
			continue;

		skill_abra_db[i].req_lv=atoi(split[2]);
		skill_abra_db[i].per=atoi(split[3]);

		++k;
		if(k >= MAX_SKILL_ABRA_DB)
			break;
	}
	fclose(fp);
	ShowStatus("Done reading '"CL_WHITE"%d"CL_RESET"' entries in '"CL_WHITE"%s"CL_RESET"'.\n",k,"db/abra_db.txt");

	fp=basics::safefopen("db/skill_castnodex_db.txt","r");
	if(fp==NULL){
		ShowError("can't read %s\n","db/skill_castnodex_db.txt");
		return 1;
	}
	while(fgets(line,sizeof(line),fp)){
		char *split[50];
		if( !is_valid_line(line) )
			continue;
		memset(split,0,sizeof(split));
		j = skill_split_str(line,split,3);
		if(split[0]==0) //fixed by Lupus
			continue;
		i=atoi(split[0]);
		if (i>=10000 && i<10015) // for guild skills [Celest]
			i -= 9500;
		else if(i<=0 || i>MAX_SKILL_DB)
			continue;

		skill_split_atoi(split[1],skill_db[i].castnodex);
		if (!split[2])
			continue;
		skill_split_atoi(split[2],skill_db[i].delaynodex);
	}
	fclose(fp);
	ShowStatus("Done reading '"CL_WHITE"%s"CL_RESET"'.\n","db/skill_castnodex_db.txt");

	fp=basics::safefopen("db/skill_nocast_db.txt","r");
	if(fp==NULL){
		ShowError("can't read %s\n","db/skill_nocast_db.txt");
		return 1;
	}
	k=0;
	while(fgets(line,sizeof(line),fp)){
		char *split[16];
		if( !is_valid_line(line) )
			continue;
		memset(split,0,sizeof(split));
		j = skill_split_str(line,split,2);
		if(split[0]==0) //fixed by Lupus
			continue;
		i=atoi(split[0]);
		if (i>=10000 && i<10015) // for guild skills [Celest]
			i -= 9500;
		else if(i<=0 || i>MAX_SKILL_DB)
			continue;
		skill_db[i].nocast=atoi(split[1]);
		++k;
	}
	fclose(fp);
	ShowStatus("Done reading '"CL_WHITE"%s"CL_RESET"'.\n","db/skill_nocast_db");

	return 0;
}

/*===============================================
 * For reading leveluseskillspamount.txt [Celest]
 *-----------------------------------------------
 */
int skill_read_skillspamount(void)
{
	char *buf,*p;
	struct skill_db *skill = NULL;
	int s, idx, new_flag=1, level=0, sp=0;

	buf=(char *)grfio_read("data\\leveluseskillspamount.txt", s);

	if(buf==NULL)
		return -1;

	buf[s]=0;
	for(p=buf;p-buf<s;)
	{
		char buf2[64];

		if (sscanf(p,"%64[@]",buf2) == 1)
		{
			level = 0;
			new_flag = 1;
		}
		else if (new_flag && sscanf(p,"%64[^#]#",buf2) == 1)
		{
			for (idx=0; skill_names[idx].id != 0; ++idx)
			{
				if (strstr(buf2, skill_names[idx].name) != NULL)
				{
					skill = &skill_db[ skill_names[idx].id ];
					new_flag = 0;
					break;
				}
			}
		}
		else if (!new_flag && sscanf(p,"%d#",&sp) == 1)
		{
			if(level<MAX_SKILL_LEVEL)
			{
				skill->sp[level]=sp;
				++level;
			}
		}

		p=strchr(p,10);
		if(!p) break;
		++p;
	}
	delete[] buf;
	ShowStatus("Done reading '"CL_WHITE"%s"CL_RESET"'.\n","data\\leveluseskillspamount.txt");

	return 0;
}

void skill_reload(void)
{
	skill_readdb();
	if (config.skill_sp_override_grffile)
		skill_read_skillspamount();
}

/*==========================================
 * �X�L��?�W������?��
 *------------------------------------------
 */
int do_init_skill(void)
{
	skill_readdb();
	if (config.skill_sp_override_grffile)
		skill_read_skillspamount();

	add_timer_func_list(skill_unit_timer,"skill_unit_timer");
	add_timer_func_list(skill_castend_id,"skill_castend_id");
	add_timer_func_list(skill_castend_pos,"skill_castend_pos");
	add_timer_func_list(skill_timerskill,"skill_timerskill");
	add_timer_func_list(skill_castend_delay_sub,"skill_castend_delay_sub");
	
	add_timer_interval(gettick()+SKILLUNITTIMER_INVERVAL, SKILLUNITTIMER_INVERVAL, skill_unit_timer,0,0);

	return 0;
}
