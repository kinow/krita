/*  This file is part of the KDE project

    Copyright (c) 2011 Sven Langkamp <sven.langkamp@gmail.com>
    Copyright (c) 2011 Srikanth Tiyyagura <srikanth.tulasiram@gmail.com>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef KORESOURCETAGGING_H
#define KORESOURCETAGGING_H


#include <kdebug.h>
#include <KoResource.h>
#include <qdom.h>
#include "kowidgets_export.h"

/**
 * KoResourceTagging allows to add and delete tags to resources and also search reources using tags
 */
class KOWIDGETS_EXPORT KoResourceTagging {

public:

    /**
    * Constructs a KoResourceTagging object
    *
    */
    KoResourceTagging(const QString& extensions);
    ~KoResourceTagging();

    QStringList getAssignedTagsList(KoResource* resource);

    void addTag(KoResource* resource,const QString& tag);

    void delTag(KoResource* resource,const QString& tag);

    QStringList getTagNamesList();

    QStringList searchTag(const QString& tag);

private:
    void readXMLFile();
    void writeXMLFile();
    /// To check whether the resource belongs to the present server or not
    bool isServerResource(QString resourceName);
    void addTag(const QString& fileName,const QString& tag);
    /// If resource filenames have no extensions, then we add "-krita.extension".
    QString getAdjustedFileName(QString fileName);
    /// Removes the adjustements before going to the server
    QStringList removeAdjustedFileNames(QStringList fileNamesList);

    QMultiHash<QString, QString> m_tagRepo;
    QHash<QString, int> m_tagList;
    QString m_tagsXMLFile;
    QString m_serverExtensions;


};


#endif // KORESOURCETAGGING_H