/*
 *  File:         tz_table.h
 *
 *  Author:       Beat Forster
 *
 *  Time zone information.
 *  Automatically generated with 'read_tzi'
 *  Conversion date: 08/10/08
 *
 *  Copyright (c) 2004-2009 by Synthesis AG (www.synthesis.ch)
 *
 */



#ifndef TZ_TABLE_H
#define TZ_TABLE_H

typedef enum {
  // special time zones
  tctx_tz_unknown,                  //   0
  tctx_tz_system,                   //   0

  // list of all Registry time zones
  tctx_tz_Afghanistan,              //   4.5  Kabul
  tctx_tz_AKST_AKDT,                //  -9    Alaska
  tctx_tz_AKST_AKDT_2006,           //  -9    Alaska
  tctx_tz_AKST_AKDT_2007,           //  -9    Alaska
  tctx_tz_HNY_NAY,                  //  -9    Alaska
  tctx_tz_HNY_NAY_2006,             //  -9    Alaska
  tctx_tz_HNY_NAY_2007,             //  -9    Alaska
  tctx_tz_Alaskan,                  //  -9    Alaska
  tctx_tz_Alaskan_2006,             //  -9    Alaska
  tctx_tz_Alaskan_2007,             //  -9    Alaska
  tctx_tz_Arab,                     //   3    Kuwait, Er Riad
  tctx_tz_Arabian,                  //   4    Abu Dhabi, Muskat
  tctx_tz_Arabic,                   //   3    Bagdad
  tctx_tz_AST_ADT,                  //  -4    Atlantik (Kanada)
  tctx_tz_AST_ADT_2006,             //  -4    Atlantik (Kanada)
  tctx_tz_AST_ADT_2007,             //  -4    Atlantik (Kanada)
  tctx_tz_HNA_HAA,                  //  -4    Atlantik (Kanada)
  tctx_tz_HNA_HAA_2006,             //  -4    Atlantik (Kanada)
  tctx_tz_HNA_HAA_2007,             //  -4    Atlantik (Kanada)
  tctx_tz_Atlantic,                 //  -4    Atlantik (Kanada)
  tctx_tz_Atlantic_2006,            //  -4    Atlantik (Kanada)
  tctx_tz_Atlantic_2007,            //  -4    Atlantik (Kanada)
  tctx_tz_AUS_Central,              //   9.5  Darwin
  tctx_tz_AUS_Eastern,              //  10    Canberra, Melbourne, Sydney
  tctx_tz_Azerbaijan,               //   4    Baku
  tctx_tz_Azores,                   //  -1    Azoren
  tctx_tz_Canada_Central,           //  -6    Saskatchewan
  tctx_tz_Cape_Verde,               //  -1    Kapverdische Inseln
  tctx_tz_Caucasus,                 //   4    Eriwan
  tctx_tz_ACST_ACDT,                //   9.5  Adelaide
  tctx_tz_Central_Australia,        //   9.5  Adelaide
  tctx_tz_Central_America,          //  -6    Zentralamerika
  tctx_tz_Central_Asia,             //   6    Astana, Dhaka
  tctx_tz_Central_Brazilian,        //  -4    Manaus
  tctx_tz_Central_Brazilian_2006,   //  -4    Manaus
  tctx_tz_Central_Brazilian_2007,   //  -4    Manaus
  tctx_tz_CET_CEST,                 //   1    Belgrad, Bratislava, Budapest, Ljubljana, Prag
  tctx_tz_MEZ_MESZ,                 //   1    Belgrad, Bratislava, Budapest, Ljubljana, Prag
  tctx_tz_Central_Europe,           //   1    Belgrad, Bratislava, Budapest, Ljubljana, Prag
  tctx_tz_Central_European,         //   1    Sarajevo, Skopje, Warschau, Zagreb
  tctx_tz_Central_Pacific,          //  11    Magadan, Salomonen, Neukaledonien
  tctx_tz_CST_CDT,                  //  -6    Chicago, Dallas, Kansas City, Winnipeg
  tctx_tz_CST_CDT_2006,             //  -6    Chicago, Dallas, Kansas City, Winnipeg
  tctx_tz_CST_CDT_2007,             //  -6    Chicago, Dallas, Kansas City, Winnipeg
  tctx_tz_HNC_HAC,                  //  -6    Chicago, Dallas, Kansas City, Winnipeg
  tctx_tz_HNC_HAC_2006,             //  -6    Chicago, Dallas, Kansas City, Winnipeg
  tctx_tz_HNC_HAC_2007,             //  -6    Chicago, Dallas, Kansas City, Winnipeg
  tctx_tz_Central,                  //  -6    Chicago, Dallas, Kansas City, Winnipeg
  tctx_tz_Central_2006,             //  -6    Chicago, Dallas, Kansas City, Winnipeg
  tctx_tz_Central_2007,             //  -6    Chicago, Dallas, Kansas City, Winnipeg
  tctx_tz_Central_Mexico,           //  -6    Guadalajara, Mexiko-Stadt, Monterrey - neu
  tctx_tz_China,                    //   8    Peking, Chongqing, Hongkong, Urumchi
  tctx_tz_Dateline,                 // -12    Internationale Datumsgrenze (Westen)
  tctx_tz_East_Africa,              //   3    Nairobi
  tctx_tz_AEST_AEDT,                //  10    Brisbane
  tctx_tz_East_Australia,           //  10    Brisbane
  tctx_tz_EET_EEST,                 //   2    Minsk
  tctx_tz_East_Europe,              //   2    Minsk
  tctx_tz_East_South_America,       //  -3    Brasilia
  tctx_tz_East_South_America_2006,  //  -3    Brasilia
  tctx_tz_East_South_America_2007,  //  -3    Brasilia
  tctx_tz_EST_EDT,                  //  -5    New York, Miami, Atlanta, Detroit, Toronto
  tctx_tz_EST_EDT_2006,             //  -5    New York, Miami, Atlanta, Detroit, Toronto
  tctx_tz_EST_EDT_2007,             //  -5    New York, Miami, Atlanta, Detroit, Toronto
  tctx_tz_HNE_HAE,                  //  -5    New York, Miami, Atlanta, Detroit, Toronto
  tctx_tz_HNE_HAE_2006,             //  -5    New York, Miami, Atlanta, Detroit, Toronto
  tctx_tz_HNE_HAE_2007,             //  -5    New York, Miami, Atlanta, Detroit, Toronto
  tctx_tz_Eastern,                  //  -5    New York, Miami, Atlanta, Detroit, Toronto
  tctx_tz_Eastern_2006,             //  -5    New York, Miami, Atlanta, Detroit, Toronto
  tctx_tz_Eastern_2007,             //  -5    New York, Miami, Atlanta, Detroit, Toronto
  tctx_tz_Egypt,                    //   2    Kairo
  tctx_tz_Ekaterinburg,             //   5    Jekaterinburg
  tctx_tz_Fiji,                     //  12    Fidschi, Kamtschatka, Marshall-Inseln
  tctx_tz_FLE,                      //   2    Helsinki, Kiew, Riga, Sofia, Tallinn, Wilna
  tctx_tz_Georgian,                 //   3    Tiflis
  tctx_tz_GMT,                      //   0    Dublin, Edinburgh, Lissabon, London
  tctx_tz_Greenland,                //  -3    Grönland
  tctx_tz_Greenwich,                //   0    Casablanca, Monrovia, Reykjavík
  tctx_tz_GTB,                      //   2    Athen, Bukarest, Istanbul
  tctx_tz_HAST_HADT,                // -10    Hawaii
  tctx_tz_Hawaiian,                 // -10    Hawaii
  tctx_tz_India,                    //   5.5  Chennai, Kolkata, Mumbai, Neu-Delhi
  tctx_tz_Iran,                     //   3.5  Teheran
  tctx_tz_Iran_2005,                //   3.5  Teheran
  tctx_tz_Iran_2006,                //   3.5  Teheran
  tctx_tz_Israel,                   //   2    Jerusalem
  tctx_tz_Israel_2004,              //   2    Jerusalem
  tctx_tz_Israel_2005,              //   2    Jerusalem
  tctx_tz_Israel_2006,              //   2    Jerusalem
  tctx_tz_Israel_2007,              //   2    Jerusalem
  tctx_tz_Israel_2008,              //   2    Jerusalem
  tctx_tz_Israel_2009,              //   2    Jerusalem
  tctx_tz_Israel_2010,              //   2    Jerusalem
  tctx_tz_Israel_2011,              //   2    Jerusalem
  tctx_tz_Israel_2012,              //   2    Jerusalem
  tctx_tz_Israel_2013,              //   2    Jerusalem
  tctx_tz_Israel_2014,              //   2    Jerusalem
  tctx_tz_Israel_2015,              //   2    Jerusalem
  tctx_tz_Israel_2016,              //   2    Jerusalem
  tctx_tz_Israel_2017,              //   2    Jerusalem
  tctx_tz_Israel_2018,              //   2    Jerusalem
  tctx_tz_Israel_2019,              //   2    Jerusalem
  tctx_tz_Israel_2020,              //   2    Jerusalem
  tctx_tz_Israel_2021,              //   2    Jerusalem
  tctx_tz_Israel_2022,              //   2    Jerusalem
  tctx_tz_Israel_2023,              //   2    Jerusalem
  tctx_tz_Jordan,                   //   2    Amman
  tctx_tz_Korea,                    //   9    Seoul
  tctx_tz_Mexico,                   //  -6    Guadalajara, Mexiko-Stadt, Monterrey - alt
  tctx_tz_Mexico_2,                 //  -7    Chihuahua, La Paz, Mazatlan - alt
  tctx_tz_Mid_Atlantic,             //  -2    Mittelatlantik
  tctx_tz_Middle_East,              //   2    Beirut
  tctx_tz_Montevideo,               //  -3    Montevideo
  tctx_tz_MST_MDT,                  //  -7    Denver, Salt Lake City, Calgary
  tctx_tz_MST_MDT_2006,             //  -7    Denver, Salt Lake City, Calgary
  tctx_tz_MST_MDT_2007,             //  -7    Denver, Salt Lake City, Calgary
  tctx_tz_HNR_HAR,                  //  -7    Denver, Salt Lake City, Calgary
  tctx_tz_HNR_HAR_2006,             //  -7    Denver, Salt Lake City, Calgary
  tctx_tz_HNR_HAR_2007,             //  -7    Denver, Salt Lake City, Calgary
  tctx_tz_Mountain,                 //  -7    Denver, Salt Lake City, Calgary
  tctx_tz_Mountain_2006,            //  -7    Denver, Salt Lake City, Calgary
  tctx_tz_Mountain_2007,            //  -7    Denver, Salt Lake City, Calgary
  tctx_tz_Mountain_Mexico,          //  -7    Chihuahua, La Paz, Mazatlan - neu
  tctx_tz_Myanmar,                  //   6.5  Yangon (Rangun)
  tctx_tz_North_Central_Asia,       //   6    Almaty, Nowosibirsk
  tctx_tz_Namibia,                  //   2    Windhuk
  tctx_tz_Nepal,                    //   5.75 Katmandu
  tctx_tz_New_Zealand,              //  12    Auckland, Wellington
  tctx_tz_NST_NDT,                  //  -3.5  Neufundland
  tctx_tz_NST_NDT_2006,             //  -3.5  Neufundland
  tctx_tz_NST_NDT_2007,             //  -3.5  Neufundland
  tctx_tz_HNT_HAT,                  //  -3.5  Neufundland
  tctx_tz_HNT_HAT_2006,             //  -3.5  Neufundland
  tctx_tz_HNT_HAT_2007,             //  -3.5  Neufundland
  tctx_tz_Newfoundland,             //  -3.5  Neufundland
  tctx_tz_Newfoundland_2006,        //  -3.5  Neufundland
  tctx_tz_Newfoundland_2007,        //  -3.5  Neufundland
  tctx_tz_North_Asia_East,          //   8    Irkutsk, Ulan Bator
  tctx_tz_North_Asia,               //   7    Krasnojarsk
  tctx_tz_Pacific_SA,               //  -4    Santiago
  tctx_tz_PST_PDT,                  //  -8    Pacific (USA, Kanada)
  tctx_tz_PST_PDT_2006,             //  -8    Pacific (USA, Kanada)
  tctx_tz_PST_PDT_2007,             //  -8    Pacific (USA, Kanada)
  tctx_tz_HNP_HAP,                  //  -8    Pacific (USA, Kanada)
  tctx_tz_HNP_HAP_2006,             //  -8    Pacific (USA, Kanada)
  tctx_tz_HNP_HAP_2007,             //  -8    Pacific (USA, Kanada)
  tctx_tz_Pacific,                  //  -8    Pacific (USA, Kanada)
  tctx_tz_Pacific_2006,             //  -8    Pacific (USA, Kanada)
  tctx_tz_Pacific_2007,             //  -8    Pacific (USA, Kanada)
  tctx_tz_Pacific_Mexico,           //  -8    Tijuana, Niederkalifornien (Mexiko)
  tctx_tz_Romance,                  //   1    Brüssel, Kopenhagen, Madrid, Paris
  tctx_tz_Russian,                  //   3    Moskau, St. Petersburg, Wolgograd
  tctx_tz_SA_Eastern,               //  -3    Buenos Aires, Georgetown
  tctx_tz_SA_Pacific,               //  -5    Bogotá, Lima, Quito, Rio Branco
  tctx_tz_SA_Western,               //  -4    Caracas, La Paz
  tctx_tz_Samoa,                    // -11    Midway-Inseln, Samoa
  tctx_tz_SE_Asia,                  //   7    Bangkok, Hanoi, Jakarta
  tctx_tz_Singapore,                //   8    Kuala Lumpur, Singapur
  tctx_tz_South_Africa,             //   2    Harare, Prätoria
  tctx_tz_Sri_Lanka,                //   5.5  Sri Jayawardenepura
  tctx_tz_Taipei,                   //   8    Taipeh
  tctx_tz_Tasmania,                 //  10    Hobart
  tctx_tz_Tokyo,                    //   9    Osaka, Sapporo, Tokio
  tctx_tz_Tonga,                    //  13    Nuku'alofa
  tctx_tz_US_Eastern,               //  -5    Indiana (Ost)
  tctx_tz_US_Mountain,              //  -7    Arizona
  tctx_tz_Vladivostok,              //  10    Wladiwostok
  tctx_tz_West_Australia,           //   8    Perth
  tctx_tz_West_Australia_2005,      //   8    Perth
  tctx_tz_West_Australia_2006,      //   8    Perth
  tctx_tz_West_Australia_2007,      //   8    Perth
  tctx_tz_West_Central_Africa,      //   1    West-Zentralafrika
  tctx_tz_WET_WEST,                 //   1    Amsterdam, Berlin, Bern, Rom, Stockholm, Wien
  tctx_tz_West_Europe,              //   1    Amsterdam, Berlin, Bern, Rom, Stockholm, Wien
  tctx_tz_West_Asia,                //   5    Islamabad, Karatschi, Taschkent
  tctx_tz_West_Pacific,             //  10    Guam, Port Moresby
  tctx_tz_Yakutsk,                  //   9    Jakutsk

  // http://www.timeanddate.com/library/abbreviations/timezones
  tctx_tz_A,                        //   1    Alpha Time Zone                  <Military>
  tctx_tz_ACDT,                     //  10.5  Australian Central Daylight Time   Australia
  tctx_tz_ACST,                     //   9.5  Australian Central Standard Time   Australia
  tctx_tz_ADT,                      //  -3    Atlantic Daylight Time            North America
  tctx_tz_AEDT,                     //  11    Australian Eastern Daylight Time   Australia
  tctx_tz_AEST,                     //  10    Australian Eastern Standard Time   Australia
  tctx_tz_AKDT,                     //  -8    Alaska Daylight Time              North America
  tctx_tz_AKST,                     //  -9    Alaska Standard Time              North America
  tctx_tz_AST,                      //  -4    Atlantic Standard Time            North America
  tctx_tz_AWST,                     //   8    Australian Western Standard Time   Australia
  tctx_tz_B,                        //   2    Bravo Time Zone                  <Military>
  tctx_tz_BST,                      //   1    British Summer Time               Europe
  tctx_tz_C,                        //   3    Charlie Time Zone                <Military>
  tctx_tz_CDT,                      //  -5    Central Daylight Time             North America
  tctx_tz_CEST,                     //   2    Central European Summer Time      Europe
  tctx_tz_CET,                      //   1    Central European Time             Europe
  tctx_tz_CST,                      //  -6    Central Standard Time             North America
  tctx_tz_CXT,                      //   7    Christmas Island Time             Australia
  tctx_tz_D,                        //   4    Delta Time Zone                  <Military>
  tctx_tz_E,                        //   5    Echo Time Zone                   <Military>
  tctx_tz_EDT,                      //  -4    Eastern Daylight Time             North America
  tctx_tz_EEST,                     //   3    Eastern European Summer Time      Europe
  tctx_tz_EET,                      //   2    Eastern European Time             Europe
  tctx_tz_EST,                      //  -5    Eastern Standard Time             North America
  tctx_tz_F,                        //   6    Foxtrot Time Zone                <Military>
  tctx_tz_G,                        //   7    Golf Time Zone                   <Military>
  tctx_tz_H,                        //   8    Hotel Time Zone                  <Military>
  tctx_tz_HAA,                      //  -3    Heure Avancée de l'Atlantique     North America
  tctx_tz_HAC,                      //  -5    Heure Avancée du Centre           North America
  tctx_tz_HADT,                     //  -9    Hawaii-Aleutian Daylight Time     North America
  tctx_tz_HAE,                      //  -4    Heure Avancée de l'Est            North America
  tctx_tz_HAP,                      //  -7    Heure Avancée du Pacifique        North America
  tctx_tz_HAR,                      //  -6    Heure Avancée des Rocheuses       North America
  tctx_tz_HAST,                     // -10    Hawaii-Aleutian Standard Time     North America
  tctx_tz_HAT,                      //  -1.5  Heure Avancée de Terre-Neuve      North America
  tctx_tz_HAY,                      //  -8    Heure Avancée du Yukon            North America
  tctx_tz_HNA,                      //  -4    Heure Normale de l'Atlantique     North America
  tctx_tz_HNC,                      //  -6    Heure Normale du Centre           North America
  tctx_tz_HNE,                      //  -5    Heure Normale de l'Est            North America
  tctx_tz_HNP,                      //  -8    Heure Normale du Pacifique        North America
  tctx_tz_HNR,                      //  -7    Heure Normale des Rocheuses       North America
  tctx_tz_HNT,                      //  -2.5  Heure Normale de Terre-Neuve      North America
  tctx_tz_HNY,                      //  -9    Heure Normale du Yukon            North America
  tctx_tz_I,                        //   9    India Time Zone                  <Military>
  tctx_tz_IST,                      //   1    Irish Summer Time                 Europe
  tctx_tz_K,                        //  10    Kilo Time Zone                   <Military>
  tctx_tz_L,                        //  11    Lima Time Zone                   <Military>
  tctx_tz_M,                        //  12    Mike Time Zone                   <Military>
  tctx_tz_MDT,                      //  -6    Mountain Daylight Time            North America
  tctx_tz_MESZ,                     //   2    Mitteleuropäische Sommerzeit      Europe
  tctx_tz_MEZ,                      //   1    Mitteleuropäische Zeit            Europe
  tctx_tz_MST,                      //  -7    Mountain Standard Time            North America
  tctx_tz_N,                        //  -1    November Time Zone               <Military>
  tctx_tz_NDT,                      //  -1.5  Newfoundland Daylight Time        North America
  tctx_tz_NFT,                      //  11.5  Norfolk (Island) Time             Australia
  tctx_tz_NST,                      //  -2.5  Newfoundland Standard Time        North America
  tctx_tz_O,                        //  -2    Oscar Time Zone                  <Military>
  tctx_tz_P,                        //  -3    Papa Time Zone                   <Military>
  tctx_tz_PDT,                      //  -7    Pacific Daylight Time             North America
  tctx_tz_PST,                      //  -8    Pacific Standard Time             North America
  tctx_tz_Q,                        //  -4    Quebec Time Zone                 <Military>
  tctx_tz_R,                        //  -5    Romeo Time Zone                  <Military>
  tctx_tz_S,                        //  -6    Sierra Time Zone                 <Military>
  tctx_tz_T,                        //  -7    Tango Time Zone                  <Military>
  tctx_tz_U,                        //  -8    Uniform Time Zone                <Military>
  tctx_tz_UTC,                      //   0    Coordinated Universal Time        Europe
  tctx_tz_V,                        //  -9    Victor Time Zone                 <Military>
  tctx_tz_W,                        // -10    Whiskey Time Zone                <Military>
  tctx_tz_WEST,                     //   1    Western European Summer Time      Europe
  tctx_tz_WET,                      //   0    Western European Time             Europe
  tctx_tz_WST,                      //   8    Western Standard Time             Australia
  tctx_tz_X,                        // -11    X-ray Time Zone                  <Military>
  tctx_tz_Y,                        // -12    Yankee Time Zone                 <Military>
  tctx_tz_Z,                        //   0    Zulu Time Zone                   <Military>

  // size of enum
  tctx_numtimezones
} TTimeZones;



typedef struct {
          short wMonth;
          short wDayOfWeek;
          short wNth;      // nth occurance
          short wHour;
          short wMinute;
        } tChange;


typedef struct {
          const char* name;
          short       bias;
          short       biasDST;
          const char* ident;
          const char* dynYear;
          tChange     dst;
          tChange     std;
        } tz_entry;


#ifdef TIMEZONES_INTERNAL
const tz_entry tz[tctx_numtimezones] =
{
  { "unknown",               0,  0, "x",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   0
  { "system",                0,  0, "x",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   0

  { "Afghanistan",         270,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   4.5
  { "AKST/AKDT",          -540, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -9
  { "AKST/AKDT",          -540, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -9
  { "AKST/AKDT",          -540, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -9
  { "HNY/NAY",            -540, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -9
  { "HNY/NAY",            -540, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -9
  { "HNY/NAY",            -540, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -9
  { "Alaskan",            -540, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -9
  { "Alaskan",            -540, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -9
  { "Alaskan",            -540, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -9
  { "Arab",                180,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   3
  { "Arabian",             240,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   4
  { "Arabic",              180, 60, " ",    "", {  4, 0,1, 3,0 },  { 10, 0,1, 4,0 } },  //   3
  { "AST/ADT",            -240, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -4
  { "AST/ADT",            -240, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -4
  { "AST/ADT",            -240, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -4
  { "HNA/HAA",            -240, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -4
  { "HNA/HAA",            -240, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -4
  { "HNA/HAA",            -240, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -4
  { "Atlantic",           -240, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -4
  { "Atlantic",           -240, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -4
  { "Atlantic",           -240, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -4
  { "AUS_Central",         570,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   9.5
  { "AUS_Eastern",         600, 60, " ",    "", { 10, 0,5, 2,0 },  {  3, 0,5, 3,0 } },  //  10
  { "Azerbaijan",          240, 60, " ",    "", {  3, 0,5, 4,0 },  { 10, 0,5, 5,0 } },  //   4
  { "Azores",              -60, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //  -1
  { "Canada_Central",     -360,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -6
  { "Cape_Verde",          -60,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -1
  { "Caucasus",            240, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   4
  { "ACST/ACDT",           570, 60, " ",    "", { 10, 0,5, 2,0 },  {  3, 0,5, 3,0 } },  //   9.5
  { "Central_Australia",   570, 60, " ",    "", { 10, 0,5, 2,0 },  {  3, 0,5, 3,0 } },  //   9.5
  { "Central_America",    -360,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -6
  { "Central_Asia",        360,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   6
  { "Central_Brazilian",  -240, 60, " ",    "", { 11, 0,1, 0,0 },  {  2, 0,5, 0,0 } },  //  -4
  { "Central_Brazilian",  -240, 60, " ","2006", { 11, 0,1, 0,0 },  {  2, 0,2, 2,0 } },  //  -4
  { "Central_Brazilian",  -240, 60, " ","2007", { 11, 0,1, 0,0 },  {  2, 0,5, 0,0 } },  //  -4
  { "CET/CEST",             60, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   1
  { "MEZ/MESZ",             60, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   1
  { "Central_Europe",       60, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   1
  { "Central_European",     60, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   1
  { "Central_Pacific",     660,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  11
  { "CST/CDT",            -360, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -6
  { "CST/CDT",            -360, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -6
  { "CST/CDT",            -360, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -6
  { "HNC/HAC",            -360, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -6
  { "HNC/HAC",            -360, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -6
  { "HNC/HAC",            -360, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -6
  { "Central",            -360, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -6
  { "Central",            -360, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -6
  { "Central",            -360, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -6
  { "Central_Mexico",     -360, 60, " ",    "", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -6
  { "China",               480,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   8
  { "Dateline",           -720,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  // -12
  { "East_Africa",         180,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   3
  { "AEST/AEDT",           600,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  10
  { "East_Australia",      600,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  10
  { "EET/EEST",            120, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   2
  { "East_Europe",         120, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   2
  { "East_South_America", -180, 60, " ",    "", { 11, 0,1, 0,0 },  {  2, 0,5, 0,0 } },  //  -3
  { "East_South_America", -180, 60, " ","2006", { 11, 0,1, 0,0 },  {  2, 0,2, 2,0 } },  //  -3
  { "East_South_America", -180, 60, " ","2007", { 11, 0,1, 0,0 },  {  2, 0,5, 0,0 } },  //  -3
  { "EST/EDT",            -300, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -5
  { "EST/EDT",            -300, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -5
  { "EST/EDT",            -300, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -5
  { "HNE/HAE",            -300, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -5
  { "HNE/HAE",            -300, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -5
  { "HNE/HAE",            -300, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -5
  { "Eastern",            -300, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -5
  { "Eastern",            -300, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -5
  { "Eastern",            -300, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -5
  { "Egypt",               120, 60, " ",    "", {  4, 4,5,23,59 }, {  9, 4,5,23,59 }},  //   2
  { "Ekaterinburg",        300, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   5
  { "Fiji",                720,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  12
  { "FLE",                 120, 60, " ",    "", {  3, 0,5, 3,0 },  { 10, 0,5, 4,0 } },  //   2
  { "Georgian",            180,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   3
  { "GMT",                   0, 60, " ",    "", {  3, 0,5, 1,0 },  { 10, 0,5, 2,0 } },  //   0
  { "Greenland",          -180, 60, " ",    "", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -3
  { "Greenwich",             0,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   0
  { "GTB",                 120, 60, " ",    "", {  3, 0,5, 3,0 },  { 10, 0,5, 4,0 } },  //   2
  { "HAST/HADT",          -600,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  // -10
  { "Hawaiian",           -600,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  // -10
  { "India",               330,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   5.5
  { "Iran",                210,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   3.5
  { "Iran",                210, 60, " ","2005", {  3, 0,1, 2,0 },  {  9, 2,4, 2,0 } },  //   3.5
  { "Iran",                210,  0, " ","2006", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   3.5
  { "Israel",              120, 60, " ",    "", {  3, 5,5, 2,0 },  {  9, 0,3, 2,0 } },  //   2
  { "Israel",              120,  0, " ","2004", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   2
  { "Israel",              120, 60, " ","2005", {  4,-1,1, 2,0 },  { 10,-1,9, 2,0 } },  //   2
  { "Israel",              120, 60, " ","2006", {  3,-1,31,2,0 },  { 10,-1,1, 2,0 } },  //   2
  { "Israel",              120, 60, " ","2007", {  3,-1,30,2,0 },  {  9,-1,16,2,0 } },  //   2
  { "Israel",              120, 60, " ","2008", {  3,-1,28,2,0 },  { 10,-1,5, 2,0 } },  //   2
  { "Israel",              120, 60, " ","2009", {  3,-1,27,2,0 },  {  9,-1,27,2,0 } },  //   2
  { "Israel",              120, 60, " ","2010", {  3,-1,26,2,0 },  {  9,-1,12,2,0 } },  //   2
  { "Israel",              120, 60, " ","2011", {  4,-1,1, 2,0 },  { 10,-1,2, 2,0 } },  //   2
  { "Israel",              120, 60, " ","2012", {  3,-1,30,2,0 },  {  9,-1,23,2,0 } },  //   2
  { "Israel",              120, 60, " ","2013", {  3,-1,29,2,0 },  {  9,-1,8, 2,0 } },  //   2
  { "Israel",              120, 60, " ","2014", {  3,-1,28,2,0 },  {  9,-1,28,2,0 } },  //   2
  { "Israel",              120, 60, " ","2015", {  3,-1,27,2,0 },  {  9,-1,20,2,0 } },  //   2
  { "Israel",              120, 60, " ","2016", {  4,-1,1, 2,0 },  { 10,-1,9, 2,0 } },  //   2
  { "Israel",              120, 60, " ","2017", {  3,-1,31,2,0 },  {  9,-1,24,2,0 } },  //   2
  { "Israel",              120, 60, " ","2018", {  3,-1,30,2,0 },  {  9,-1,16,2,0 } },  //   2
  { "Israel",              120, 60, " ","2019", {  3,-1,29,2,0 },  { 10,-1,6, 2,0 } },  //   2
  { "Israel",              120, 60, " ","2020", {  3,-1,27,2,0 },  {  9,-1,27,2,0 } },  //   2
  { "Israel",              120, 60, " ","2021", {  3,-1,26,2,0 },  {  9,-1,12,2,0 } },  //   2
  { "Israel",              120, 60, " ","2022", {  4,-1,1, 2,0 },  { 10,-1,2, 2,0 } },  //   2
  { "Israel",              120,  0, " ","2023", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   2
  { "Jordan",              120, 60, " ",    "", {  3, 4,5, 0,0 },  {  9, 5,5, 1,0 } },  //   2
  { "Korea",               540,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   9
  { "Mexico",             -360, 60, " ",    "", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -6
  { "Mexico_2",           -420, 60, " ",    "", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -7
  { "Mid_Atlantic",       -120, 60, " ",    "", {  3, 0,5, 2,0 },  {  9, 0,5, 2,0 } },  //  -2
  { "Middle_East",         120, 60, " ",    "", {  3, 0,5, 0,0 },  { 10, 6,5,23,59 }},  //   2
  { "Montevideo",         -180, 60, " ",    "", { 10, 0,1, 2,0 },  {  3, 0,2, 2,0 } },  //  -3
  { "MST/MDT",            -420, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -7
  { "MST/MDT",            -420, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -7
  { "MST/MDT",            -420, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -7
  { "HNR/HAR",            -420, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -7
  { "HNR/HAR",            -420, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -7
  { "HNR/HAR",            -420, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -7
  { "Mountain",           -420, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -7
  { "Mountain",           -420, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -7
  { "Mountain",           -420, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -7
  { "Mountain_Mexico",    -420, 60, " ",    "", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -7
  { "Myanmar",             390,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   6.5
  { "North_Central_Asia",  360, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   6
  { "Namibia",             120,-60, " ",    "", {  4, 0,1, 2,0 },  {  9, 0,1, 2,0 } },  //   2
  { "Nepal",               345,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   5.75
  { "New_Zealand",         720, 60, " ",    "", { 10, 0,1, 2,0 },  {  3, 0,3, 3,0 } },  //  12
  { "NST/NDT",            -210, 60, " ",    "", {  3, 0,2, 0,1 },  { 11, 0,1, 0,1 } },  //  -3.5
  { "NST/NDT",            -210, 60, " ","2006", {  4, 0,1, 0,1 },  { 10, 0,5, 0,0 } },  //  -3.5
  { "NST/NDT",            -210, 60, " ","2007", {  3, 0,2, 0,1 },  { 11, 0,1, 0,0 } },  //  -3.5
  { "HNT/HAT",            -210, 60, " ",    "", {  3, 0,2, 0,1 },  { 11, 0,1, 0,1 } },  //  -3.5
  { "HNT/HAT",            -210, 60, " ","2006", {  4, 0,1, 0,1 },  { 10, 0,5, 0,0 } },  //  -3.5
  { "HNT/HAT",            -210, 60, " ","2007", {  3, 0,2, 0,1 },  { 11, 0,1, 0,0 } },  //  -3.5
  { "Newfoundland",       -210, 60, " ",    "", {  3, 0,2, 0,1 },  { 11, 0,1, 0,1 } },  //  -3.5
  { "Newfoundland",       -210, 60, " ","2006", {  4, 0,1, 0,1 },  { 10, 0,5, 0,0 } },  //  -3.5
  { "Newfoundland",       -210, 60, " ","2007", {  3, 0,2, 0,1 },  { 11, 0,1, 0,0 } },  //  -3.5
  { "North_Asia_East",     480, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   8
  { "North_Asia",          420, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   7
  { "Pacific_SA",         -240, 60, " ",    "", { 10, 6,2,23,59 }, {  3, 6,2,23,59 }},  //  -4
  { "PST/PDT",            -480, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -8
  { "PST/PDT",            -480, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -8
  { "PST/PDT",            -480, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -8
  { "HNP/HAP",            -480, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -8
  { "HNP/HAP",            -480, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -8
  { "HNP/HAP",            -480, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -8
  { "Pacific",            -480, 60, " ",    "", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -8
  { "Pacific",            -480, 60, " ","2006", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -8
  { "Pacific",            -480, 60, " ","2007", {  3, 0,2, 2,0 },  { 11, 0,1, 2,0 } },  //  -8
  { "Pacific_Mexico",     -480, 60, " ",    "", {  4, 0,1, 2,0 },  { 10, 0,5, 2,0 } },  //  -8
  { "Romance",              60, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   1
  { "Russian",             180, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   3
  { "SA_Eastern",         -180,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -3
  { "SA_Pacific",         -300,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -5
  { "SA_Western",         -240,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -4
  { "Samoa",              -660,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  // -11
  { "SE_Asia",             420,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   7
  { "Singapore",           480,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   8
  { "South_Africa",        120,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   2
  { "Sri_Lanka",           330,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   5.5
  { "Taipei",              480,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   8
  { "Tasmania",            600, 60, " ",    "", { 10, 0,1, 2,0 },  {  3, 0,5, 3,0 } },  //  10
  { "Tokyo",               540,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   9
  { "Tonga",               780,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  13
  { "US_Eastern",         -300,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -5
  { "US_Mountain",        -420,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -7
  { "Vladivostok",         600, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //  10
  { "West_Australia",      480, 60, " ",    "", { 10, 0,5, 2,0 },  {  3, 0,5, 3,0 } },  //   8
  { "West_Australia",      480,  0, " ","2005", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   8
  { "West_Australia",      480, 60, " ","2006", { 12,-1,1, 2,0 },  {  1,-1,1, 0,0 } },  //   8
  { "West_Australia",      480, 60, " ","2007", { 10, 0,5, 2,0 },  {  3, 0,5, 3,0 } },  //   8
  { "West_Central_Africa",  60,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   1
  { "WET/WEST",             60, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   1
  { "West_Europe",          60, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   1
  { "West_Asia",           300,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   5
  { "West_Pacific",        600,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  10
  { "Yakutsk",             540, 60, " ",    "", {  3, 0,5, 2,0 },  { 10, 0,5, 3,0 } },  //   9

  { "A",                    60,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   1
  { "ACDT",                630,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  10.5
  { "ACST",                570,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   9.5
  { "ADT",                -180,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -3
  { "AEDT",                660,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  11
  { "AEST",                600,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  10
  { "AKDT",               -480,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -8
  { "AKST",               -540,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -9
  { "AST",                -240,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -4
  { "AWST",                480,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   8
  { "B",                   120,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   2
  { "BST",                  60,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   1
  { "C",                   180,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   3
  { "CDT",                -300,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -5
  { "CEST",                120,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   2
  { "CET",                  60,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   1
  { "CST",                -360,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -6
  { "CXT",                 420,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   7
  { "D",                   240,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   4
  { "E",                   300,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   5
  { "EDT",                -240,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -4
  { "EEST",                180,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   3
  { "EET",                 120,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   2
  { "EST",                -300,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -5
  { "F",                   360,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   6
  { "G",                   420,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   7
  { "H",                   480,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   8
  { "HAA",                -180,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -3
  { "HAC",                -300,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -5
  { "HADT",               -540,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -9
  { "HAE",                -240,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -4
  { "HAP",                -420,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -7
  { "HAR",                -360,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -6
  { "HAST",               -600,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  // -10
  { "HAT",                 -90,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -1.5
  { "HAY",                -480,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -8
  { "HNA",                -240,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -4
  { "HNC",                -360,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -6
  { "HNE",                -300,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -5
  { "HNP",                -480,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -8
  { "HNR",                -420,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -7
  { "HNT",                -150,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -2.5
  { "HNY",                -540,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -9
  { "I",                   540,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   9
  { "IST",                  60,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   1
  { "K",                   600,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  10
  { "L",                   660,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  11
  { "M",                   720,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  12
  { "MDT",                -360,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -6
  { "MESZ",                120,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   2
  { "MEZ",                  60,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   1
  { "MST",                -420,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -7
  { "N",                   -60,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -1
  { "NDT",                 -90,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -1.5
  { "NFT",                 690,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  11.5
  { "NST",                -150,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -2.5
  { "O",                  -120,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -2
  { "P",                  -180,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -3
  { "PDT",                -420,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -7
  { "PST",                -480,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -8
  { "Q",                  -240,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -4
  { "R",                  -300,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -5
  { "S",                  -360,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -6
  { "T",                  -420,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -7
  { "U",                  -480,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -8
  { "UTC",                   0,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   0
  { "V",                  -540,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //  -9
  { "W",                  -600,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  // -10
  { "WEST",                 60,  0, "d",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   1
  { "WET",                   0,  0, "s",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   0
  { "WST",                 480,  0, " ",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   8
  { "X",                  -660,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  // -11
  { "Y",                  -720,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  // -12
  { "Z",                     0,  0, "m",    "", {  0, 0,0, 0,0 },  {  0, 0,0, 0,0 } },  //   0
};
#endif


#endif
/* eof */
