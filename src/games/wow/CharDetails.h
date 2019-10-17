/*
* CharDetails.h
*
*  Created on: 26 oct. 2013
*
*/

#ifndef _CHARDETAILS_H_
#define _CHARDETAILS_H_

#include "database.h"
#include "RaceInfos.h"
#include "wow_enums.h"
#include "metaclasses/Observable.h"

class WoWModel;
class QXmlStreamWriter;
class QXmlStreamReader;


#ifdef _WIN32
#    ifdef BUILDING_WOW_DLL
#        define _CHARDETAILS_API_ __declspec(dllexport)
#    else
#        define _CHARDETAILS_API_ __declspec(dllimport)
#    endif
#else
#    define _CHARDETAILS_API_
#endif

class _CHARDETAILS_API_ CharDetails : public Observable
{
public:
  CharDetails();

  // Types
  enum BaseSectionType
  {
    SkinBaseType = 0,
    FaceBaseType = 1,
    FacialHairBaseType = 2,
    HairBaseType = 3,
    UnderwearBaseType = 4,
    Custom1BaseType = 5,
    Custom2BaseType = 6,
    Custom3BaseType = 7,
  };
  
  // Types
  enum SectionType
  {
    SkinType = 0,
    FaceType = 1,
    FacialHairType = 2,
    HairType = 3,
    UnderwearType = 4,
    SkinTypeHD = 5,
    FaceTypeHD = 6,
    FacialHairTypeHD = 7,
    HairTypeHD = 8,
    UnderwearTypeHD = 9,
    TattooType = 11,
    TattooTypeHD = 12,
    Custom2Type = 13,
    Custom2TypeHD = 14,
    Custom3Type = 15,
    Custom3TypeHD = 16
  };
  
  enum CustomizationType
  {
    SKIN_COLOR = 0,
    FACE = 1,
    FACIAL_CUSTOMIZATION_STYLE = 2,
    FACIAL_CUSTOMIZATION_COLOR = 3,
    ADDITIONAL_FACIAL_CUSTOMIZATION = 4,
    DH_TATTOO_STYLE = 5,
    DH_TATTOO_COLOR = 6,
    DH_HORN_STYLE = 7,
    DH_BLINDFOLDS = 8
  };

  class CustomizationParam
  {
  public:
    QString name;
    std::vector<int> possibleValues;
  };


  std::map<int, int> SectionTypeToHD =
  {
    { SkinType, SkinTypeHD },
    { FaceType, FaceTypeHD },
    { FacialHairType, FacialHairTypeHD },
    { HairType, HairTypeHD },
    { UnderwearType, UnderwearTypeHD },
    { TattooType, TattooTypeHD },
    { Custom2Type, Custom2TypeHD },
    { Custom3Type, Custom3TypeHD }
  };

  EyeGlowTypes eyeGlowType;

  bool showUnderwear, showEars, showHair, showFacialHair, showFeet, autoHideGeosetsForHeadItems;

  bool isNPC;

  RaceInfos infos;

  int geosets[NUM_GEOSETS];

  // save + load
  void save(QXmlStreamWriter &);
  void load(QString &);


  void reset(WoWModel *);

  void print();

  std::vector<int> getTextureForSection(BaseSectionType);


  // accessors to customization
  void set(CustomizationType type, uint val);
  uint get(CustomizationType type) const;

  CustomizationParam getParams(CustomizationType type);

  void setRandomValue(CustomizationType type);

  std::vector<CustomizationType> getCustomizationOptions() const;

  void setDemonHunterMode(bool);
  bool isDemonHunter() const { return m_isDemonHunter; }

private:
  WoWModel * m_model;

  void fillCustomizationMap();
  int getSectionType(int baseType, bool isHD);
  std::map<CustomizationType, CustomizationParam> m_customizationParamsMap;
  std::map<CustomizationType, std::map<int, CustomizationParam> > m_multiCustomizationMap;


  std::map<CustomizationType, uint> m_currentCustomization;

  bool m_isDemonHunter;
  QString m_dhModel;
};



#endif /* _CHARDETAILS_H_ */
