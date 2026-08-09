cmake_minimum_required(VERSION 3.16)

project(lumieTcg VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick Sql REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS WebSockets)

set_source_files_properties(
    qml/Core/Constants.qml
    qml/Core/Motion.qml
    qml/Core/Radius.qml
    qml/Core/Resources.qml
    qml/Core/SceneManager.qml
    qml/Core/Spacing.qml
    qml/Core/Theme.qml
    qml/Core/Typography.qml
    PROPERTIES QT_QML_SINGLETON_TYPE TRUE
)



qt_add_executable(applumieTcg
    App.cpp
)

qt_add_qml_module(applumieTcg
    URI lumieTcg
    VERSION 1.0

    SOURCES
        App.cpp
        src/Core/EnumUtils.cpp
        src/Core/EnumUtils.h
        src/Core/Enums.h
        src/Core/GameEvent.h
        src/Core/GameSnapshot.h
        src/Core/GameTypes.h
        src/Data/AssetResolver.cpp
        src/Data/AssetResolver.h
        src/Data/CardDatabase.cpp
        src/Data/CardDatabase.h
        src/Data/CharacterDatabase.cpp
        src/Data/CharacterDatabase.h
        src/Managers/AppManager.cpp
        src/Managers/AppManager.h
        src/Managers/AssetManager.cpp
        src/Managers/AssetManager.h
        src/Managers/AuthManager.cpp
        src/Managers/AuthManager.h
        src/Managers/DeckManager.cpp
        src/Managers/DeckManager.h
        src/Managers/GameManager.cpp
        src/Managers/GameManager.h
        src/Managers/MatchmakingManager.cpp
        src/Managers/MatchmakingManager.h
        src/Models/BoardModel.cpp
        src/Models/BoardModel.h
        src/Models/CardModel.cpp
        src/Models/CardModel.h
        src/Models/CharacterModel.cpp
        src/Models/CharacterModel.h
        src/Models/PlayerModel.cpp
        src/Models/PlayerModel.h
        src/Network/MessageRouter.cpp
        src/Network/MessageRouter.h
        src/Network/NetworkClient.cpp
        src/Network/NetworkClient.h
        src/Network/Protocol.cpp
        src/Network/Protocol.h
        src/Network/RealtimeTransport.cpp
        src/Network/RealtimeTransport.h

    QML_FILES
        qml/App.qml
        qml/Components/battle/DiceBar.qml
        qml/Components/battle/ElementPointBar.qml
        qml/Components/battle/EnergyBar.qml
        qml/Components/battle/HpBar.qml
        qml/Components/battle/WeatherBanner.qml
        qml/Components/cards/Card.qml
        qml/Components/cards/CharacterCard.qml
        qml/Components/cards/SupportCard.qml
        qml/Components/common/Loading.qml
        qml/Components/common/Logo.qml
        qml/Components/common/Popup.qml
        qml/Components/controls/GameButton.qml
        qml/Components/controls/GameIcon.qml
        qml/Components/controls/GameImage.qml
        qml/Components/controls/GamePanel.qml
        qml/Components/controls/GameText.qml
        qml/Components/layout/GameBackground.qml
        qml/Screens/BattleScreen.qml
        qml/Screens/CollectionScreen.qml
        qml/Screens/DeckScreen.qml
        qml/Screens/MainMenu.qml
        qml/Screens/SettingsScreen.qml
        qml/Screens/SplashScreen.qml
        qml/Core/Constants.qml
        qml/Core/Motion.qml
        qml/Core/Radius.qml
        qml/Core/Resources.qml
        qml/Core/SceneManager.qml
        qml/Core/Spacing.qml
        qml/Core/Theme.qml
        qml/Core/Typography.qml

    RESOURCES assets/backgrounds/background.png assets/cards/AbyssalSummons.png assets/cards/Adeptus'Temptation.png assets/cards/AdeptusTemptation.png assets/cards/Adventurer'sBandana.png assets/cards/AdventurersBandana.png assets/cards/AquilaFavonia.png assets/cards/ArchaicPetra.png assets/cards/Awakening.png assets/cards/BlessingoftheDivineRelic'sInstallation.png assets/cards/BlessingoftheDivineRelicsInstallation.png assets/cards/BlizzardStrayer.png assets/cards/BrokenRime'sEcho.png assets/cards/Calx'sArts.png assets/cards/CalxsArts.png assets/cards/ChangingShifts.png assets/cards/ChangtheNinth.png assets/cards/ChaoticEntropy.png assets/cards/ChefMao.png assets/cards/ColdBloodedStrike.png assets/cards/CrimsonWitchofFlames.png assets/cards/Crossfire.png assets/cards/DawnWinery.png assets/cards/DeepwoodMemories.png assets/cards/ElementalResonanceEnduringRock.png assets/cards/ElementalResonanceFerventFlames.png assets/cards/ElementalResonanceHighVoltage.png assets/cards/ElementalResonanceImpetuousWinds.png assets/cards/ElementalResonanceShatteringIce.png assets/cards/ElementalResonanceSoothingWater.png assets/cards/ElementalResonanceSprawlingGreenery.png assets/cards/ElementalResonanceWovenFlames.png assets/cards/ElementalResonanceWovenIce.png assets/cards/ElementalResonanceWovenStone.png assets/cards/ElementalResonanceWovenThunder.png assets/cards/ElementalResonanceWovenWaters.png assets/cards/ElementalResonanceWovenWeeds.png assets/cards/ElementalResonanceWovenWinds.png assets/cards/Ellin.png assets/cards/Exile'sCirclet.png assets/cards/ExilesCirclet.png assets/cards/FavoniusCathedral.png assets/cards/FeatherfallJudgment.png assets/cards/FloralSidewinder.png assets/cards/FlowingFlame.png assets/cards/Gambler'sEarrings.png assets/cards/GamblersEarrings.png assets/cards/General'sAncientHelm.png assets/cards/GloriousSeason.png assets/cards/GrandExpectation.png assets/cards/Guardian'sOath.png assets/cards/GuardiansOath.png assets/cards/HeartofDepth.png assets/cards/IGotYourBack.png assets/cards/IHaven'tLostYet!.png assets/cards/Instructor'sCap.png assets/cards/InstructorsCap.png assets/cards/IronTongueTian.png assets/cards/JadeChamber.png assets/cards/JueyunGuoba.png assets/cards/KantenSenmyouBlessing.png assets/cards/Katheryne.png assets/cards/KnightsofFavoniusLibrary.png assets/cards/LandsofDandelion.png assets/cards/LaurelCoronet.png assets/cards/LeaveIttoMe!.png assets/cards/Liben.png assets/cards/LightningStorm.png assets/cards/LithicSpear.png assets/cards/LiuSu.png assets/cards/LiyueHarborWharf.png assets/cards/LotusFlowerCrisp.png assets/cards/LuckyDog'sSilverCirclet.png assets/cards/LuckyDogsSilverCirclet.png assets/cards/MagicGuide.png assets/cards/MaskofSolitudeBasalt.png assets/cards/MasterofWeaponry.png assets/cards/MintyMeatRolls.png assets/cards/MirrorCage.png assets/cards/MondstadtHashBrown.png assets/cards/MushroomPizza.png assets/cards/NaganoharaMeteorSwarm.png assets/cards/NorthernSmokedChicken.png assets/cards/NRE.png assets/cards/OrnateKabuto.png assets/cards/PaidinFull.png assets/cards/Paimon.png assets/cards/ParametricTransformer.png assets/cards/PoundingSurprise.png assets/cards/ProliferatingSpores.png assets/cards/ProphecyofSubmersion.png assets/cards/QuickKnit.png assets/cards/RavenBow.png assets/cards/SacrificialBow.png assets/cards/SacrificialFragments.png assets/cards/SacrificialGreatsword.png assets/cards/SacrificialSword.png assets/cards/SendOff.png assets/cards/ShakenNotPurred.png assets/cards/SinofPride.png assets/cards/SkywardAtlas.png assets/cards/SkywardHarp.png assets/cards/SkywardSpine.png assets/cards/Starsigns.png assets/cards/SteadyBreathing.png assets/cards/StellarPredator.png assets/cards/StonehideReforged.png assets/cards/StrategicReserve.png assets/cards/Strategize.png assets/cards/StreamingSurge.png assets/cards/SweetMadame.png assets/cards/Tamanooya'sCasket.png assets/cards/TheBestestTravelCompanion!.png assets/cards/TheScentRemained.png assets/cards/ThunderingFury.png assets/cards/ThunderingPenance.png assets/cards/ThunderSummoner'sCrown.png assets/cards/Timaeus.png assets/cards/Timmie.png assets/cards/Toss-Up.png assets/cards/TossUp.png assets/cards/TranscendentAutomaton.png assets/cards/Traveler'sHandySword.png assets/cards/TravelingDoctor'sHandkerchief.png assets/cards/TravelingDoctorsHandkerchief.png assets/cards/Tubby.png assets/cards/tumblr_195786323add8cc91d656679deaa7fb1_7ecf8001_500.png assets/cards/tumblr_4efa494a07d692b21ed5ce2416f3cb9d_68bd67d1_500.png assets/cards/tumblr_5209112a8963b41625cc0965e0195978_5691bc7a_500.png assets/cards/tumblr_69aaf540a3526175a89beef251390ae4_cad41718_500.png assets/cards/tumblr_8019f6f2b531f31526b834cc56a8e1da_ea4ea549_500.png assets/cards/tumblr_83f82277e872e1fd5013b8549fca3b5a_5878db80_500.png assets/cards/tumblr_88120f0ed9e31df568cf5785936e81d4_74b3e2d4_500.png assets/cards/tumblr_b9293583b083ba844aa96027c56830dd_b1c09e23_500.png assets/cards/tumblr_d65e777229eaefd642bcc8c4cab3bf13_0dcfa783_500.png assets/cards/tumblr_e6b9dd77a3123b7850f3586ccacd4049_09d3994f_500.png assets/cards/UndividedHeart.png assets/cards/ViridescentVenerer'sDiadem.png assets/cards/ViridescentVenerer.png assets/cards/ViridescentVenerersDiadem.png assets/cards/Wagner.png assets/cards/WangshuInn.png assets/cards/WellspringofWarLust.png assets/cards/WhentheCraneReturned.png assets/cards/WhiteIronGreatsword.png assets/cards/WhiteTassel.png assets/cards/WineStainedTricorne.png assets/cards/Witch'sScorchingHat.png assets/cards/WitchsScorchingHat.png assets/cards/Wolf'sGravestone.png assets/characters/Barbara.png assets/characters/Beidou.png assets/characters/Bennett.png assets/characters/Chongyun.png assets/characters/Collei.png assets/characters/Cyno.png assets/characters/Dehya.png assets/characters/Diluc.png assets/characters/Diona.png assets/characters/EremiteDesertClearwater.png assets/characters/EremiteFloralRingDancer.png assets/characters/EremiteScorchingLoremaster.png assets/characters/Eula.png assets/characters/FatuiPyroAgent.png assets/characters/Fischl.png assets/characters/Ganyu.png assets/characters/JadeplumeTerrorshroom.png assets/characters/Jean.png assets/characters/Kaeya.png assets/characters/KamisatoAyaka.png assets/characters/Keqing.png assets/characters/Klee.png assets/characters/KujouSara.png assets/characters/KukiShinobu.png assets/characters/MaguuKenki.png assets/characters/MirrorMaiden.png assets/characters/Mona.png assets/characters/Nahida.png assets/characters/Ningguang.png assets/characters/Noelle.png assets/characters/Razor.png assets/characters/RhodeiaofLoch.png assets/characters/SangonomiyaKokomi.png assets/characters/StonehideLawachurl.png assets/characters/Sucrose.png assets/characters/Xiangling.png assets/characters/Xingqiu.png assets/characters/Yoimiya.png assets/costs/ANEMO.png assets/costs/ANY.png assets/costs/CRYO.png assets/costs/DENDRO.png assets/costs/ELECTRO.png assets/costs/ENERGY.png assets/costs/GEO.png assets/costs/HYDRO.png assets/costs/PYRO.png assets/costs/SAME.png assets/elements/anemo.png assets/elements/cryo.png assets/elements/dendro.png assets/elements/electro.png assets/elements/geo.png assets/elements/hydro.png assets/elements/omni.png assets/elements/pyro.png assets/energy/empty.png assets/energy/fill.png assets/equips/artifact.png assets/equips/talent.png assets/equips/weapon.png assets/fonts/genshin.ttf assets/icons/change_character.png assets/icons/confirm-icon.png assets/icons/hp.png assets/icons/none.png assets/images/card-num-icon.png assets/images/heal-icon.png assets/images/oppo-dice-icon.png assets/images/own-dice-icon.png assets/images/time-clock-grey.png assets/images/time-clock-icon.png assets/skills/Akara.png assets/skills/AllSchemestoKnow.png assets/skills/AstableAnemohypostasisCreation6308.png assets/skills/BladeAblaze.png assets/skills/Bladework.png assets/skills/BlusteringBlade.png assets/skills/BoltsofDownfall.png assets/skills/Breastplate.png assets/skills/CelestialShower.png assets/skills/CeremonialBladework.png assets/skills/ChonghuasLayeredFrost.png assets/skills/ClawandThunder.png assets/skills/CloudPartingStar.png assets/skills/DandelionBreeze.png assets/skills/Dawn.png assets/skills/Demonbane.png assets/skills/DoughFu.png assets/skills/FantasticVoyage.png assets/skills/FatalRainscreen.png assets/skills/FavoniusBladework.png assets/skills/FavoniusBladeworkMaid.png assets/skills/FeatherSpreading.png assets/skills/FireworkFlareUp.png assets/skills/FloralBrush.png assets/skills/ForbiddenCreationIsomer75TypeII.png assets/skills/FrostflakeArrow.png assets/skills/Frostgnaw.png assets/skills/FrostyAssault.png assets/skills/GaleBlade.png assets/skills/GlacialWaltz.png assets/skills/GuhuaStyle.png assets/skills/GuobaAttack.png assets/skills/GyoeiNarukamiKariyamaRite.png assets/skills/Ichimonji.png assets/skills/IcyPaws.png assets/skills/IllusoryHeart.png assets/skills/IllusoryTorrent.png assets/skills/InfluxBlast.png assets/skills/InfusedStonehide.png assets/skills/InvokersSpear.png assets/skills/JadeScreen.png assets/skills/JumpyDumpty.png assets/skills/Kaboom.png assets/skills/KamisatoArtHyouka.png assets/skills/KamisatoArtKabuki.png assets/skills/KamisatoArtSenho.png assets/skills/KamisatoArtSoumetsu.png assets/skills/Kurage'sOath.png assets/skills/KätzleinStyle.png assets/skills/LawfulEnforcer.png assets/skills/LeonineBite.png assets/skills/LettheShowBegin♪.png assets/skills/LightningFang.png assets/skills/LiutianArchery.png assets/skills/MajesticDance.png assets/skills/MidnightPhantasmagoria.png assets/skills/MirrorReflectionofDoom.png assets/skills/MoltenInferno.png assets/skills/MovoLawa.png assets/skills/Nereid'sAscension.png assets/skills/Nightrider.png assets/skills/NiwabiFireDance.png assets/skills/Oceanborne.png assets/skills/OceanidMimicSummoning.png assets/skills/PassionOverload.png assets/skills/PlamaLawa.png assets/skills/Prowl.png assets/skills/PseudoTenguSweeper.png assets/skills/Pyronado.png assets/skills/RadicalVitality.png assets/skills/Raincutter.png assets/skills/RippledReflection.png assets/skills/RippleofFate.png assets/skills/RyuukinSaxifrage.png assets/skills/SacredRiteWolfsSwiftness.png assets/skills/SanctifyingRing.png assets/skills/SandstormAssault.png assets/skills/SearingOnslaught.png assets/skills/SecretRiteChasmicSoulfarer.png assets/skills/ShiningMiracle♪.png assets/skills/Shinobu'sShadowsword.png assets/skills/SignatureMix.png assets/skills/skill-bg.png assets/skills/SparklingScatter.png assets/skills/SparksnSplash.png assets/skills/Starshatter.png assets/skills/StarwardSword.png assets/skills/StealthMaster.png assets/skills/SteelFang.png assets/skills/StellarisPhantasm.png assets/skills/StellarRestoration.png assets/skills/Stormbreaker.png assets/skills/StrikeofFortune.png assets/skills/Supplicant'sBowmanship.png assets/skills/Surge.png assets/skills/SweepingTime.png assets/skills/TemperedSword.png assets/skills/TheMyriadWilds.png assets/skills/TheShapeofWater.png assets/skills/Thrust.png assets/skills/TideandTorrent.png assets/skills/Tidecaller.png assets/skills/TrailoftheQilin.png assets/skills/Trump-CardKitty.png assets/skills/UpaShato.png assets/skills/VolatileSporeCloud.png assets/skills/WaterBall.png assets/skills/Wavestrider.png assets/skills/WhisperofWater.png assets/skills/WindSpiritCreation.png assets/skills/YunlaiSwordsmanship.png assets/states/add_hurt.png assets/states/anemo_infusion.png assets/states/CatalyzingField.png assets/states/change_cost_add.png assets/states/change_next.png assets/states/cryo_infusion.png assets/states/dendro_infusion.png assets/states/DendroCore.png assets/states/electro_infusion.png assets/states/frozen_icon.png assets/states/full.png assets/states/geo_infusion.png assets/states/heal.png assets/states/hydro_infusion.png assets/states/prepare.png assets/states/pyro_infusion.png assets/states/shield.png assets/states/state.png assets/states/sub_hurt.png assets/states/times_shield.png assets/summons/Bake-Kurage.png assets/summons/BurningFlame.png assets/summons/CryoHilichurlShooter.png assets/summons/CuileinAnbar.png assets/summons/DandelionField.png assets/summons/DrunkenMist.png assets/summons/ElectroHilichurlShooter.png assets/summons/FrostflakeSekinoTo.png assets/summons/Guoba.png assets/summons/HilichurlBerserker.png assets/summons/HydroSamachurl.png assets/summons/LargeWindSpirit.png assets/summons/LightningStiletto.png assets/summons/MelodyLoop.png assets/summons/OceanidMimicFerret.png assets/summons/OceanidMimicFrog.png assets/summons/OceanidMimicRaptor.png assets/summons/Oz.png assets/summons/Reflection.png assets/summons/SacredCryoPearl.png assets/summons/ShadowswordGallopingFrost.png assets/summons/ShadowswordLoneGale.png


)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(applumieTcg PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.applumieTcg
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(applumieTcg
    PRIVATE
        Qt6::Core
        Qt6::Quick
        Qt6::Qml
        Qt6::Network
        Qt6::WebSockets
        Qt6::Sql
)

include(GNUInstallDirs)
install(TARGETS applumieTcg
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
