/*=========================================================================

 medInria

 Copyright (c) INRIA 2013 - 2020. All rights reserved.
 See LICENSE.txt for details.
 
  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

=========================================================================*/

#include <medSettingsManager.h>

#include <QSettings>

#include <dtkLog>

class medSettingsManagerPrivate
{
public:
    QSettings settings;
};

std::unique_ptr<medSettingsManager> medSettingsManager::s_instance = nullptr;

/**
* instance - singleton access method, returns a singleViewContainer static instance of the manager
* @return   medSettingsManager & - the manager
*/
medSettingsManager &medSettingsManager::instance()
{
    if(!s_instance)
    {
        s_instance = std::unique_ptr<medSettingsManager>(new medSettingsManager());
    }
    return *s_instance.get();
}

medSettingsManager::medSettingsManager( void ): d(new medSettingsManagerPrivate)
{

}

medSettingsManager::~medSettingsManager()
{
    delete d;
    d = nullptr;
}

/**
* value
* @param: const QString & section
* @param: const QString & key
* @param: const QVariant & defaultValue
* @return   QT_NAMESPACE::QVariant
*/
QVariant medSettingsManager::value( const QString & section, const QString & key, const QVariant & defaultValue /*= QVariant() */ )
{
    bool valuePresent;

    QString sectionKey;
    sectionKey = section + "/" + key;
    valuePresent = d->settings.contains(sectionKey);

    // don't write in case of no defaultValue
    if (!defaultValue.isValid())
        valuePresent = true;

    QVariant result = d->settings.value(sectionKey, defaultValue);

    // write default value so we can share it
    if (!valuePresent)
    {
        qDebug() << "writing default value for section: " << section << " key: " << key << "value: " << defaultValue;
        setValue(section, key, result);
    }

    return result;
}

/**
* keys
* @param: const QString & section
* @return   QStringList
*/
QStringList medSettingsManager::keys ( const QString & section)
{
    d->settings.beginGroup(section);
    QStringList keys = d->settings.childKeys();
    d->settings.endGroup();

    return keys;
}

/**
* setValue
* @param: const QString & key
* @param: const QVariant & value
* @return   void
*/
void medSettingsManager::setValue( const QString & section, const QString & key, const QVariant & value )
{
    QString sectionKey;
    sectionKey = section + "/" + key;
    d->settings.setValue(sectionKey, value);
    emit settingsChanged(section);
}

/**
* remove
* @param: const QString & key
* @return   void
*/
void medSettingsManager::remove (const QString & section, const QString & key)
{
    d->settings.beginGroup(section);
    d->settings.remove(key);
    d->settings.endGroup();
}
