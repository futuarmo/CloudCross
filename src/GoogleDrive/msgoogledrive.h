/*
    CloudCross: Opensource program for syncronization of local files and folders with clouds

    Copyright (C) 2016  Vladimir Kamensky
    Copyright (C) 2016  Master Soft LLC.
    All rights reserved.


  BSD License

  Redistribution and use in source and binary forms, with or without modification, are
  permitted provided that the following conditions are met:

  - Redistributions of source code must retain the above copyright notice, this list of
    conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice, this list
    of conditions and the following disclaimer in the documentation and/or other
    materials provided with the distribution.
  - Neither the name of the "Vladimir Kamensky" or "Master Soft LLC." nor the names of
    its contributors may be used to endorse or promote products derived from this
    software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY E
  XPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES O
  F MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SH
  ALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENT
  AL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROC
  UREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS I
  NTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRI
  CT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF T
  HE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef MSGOOGLEDRIVE_H
#define MSGOOGLEDRIVE_H

#include <QObject>
#include <include/mscloudprovider.h>



class MSGoogleDrive : public MSCloudProvider
{
public:


    // create hash table from remote json file records
    bool createHashFromRemote();
    // get slice from remote files hash table by parent and some other conditions
    QHash<QString,QJsonValue> get(QString parentId, int target);
    bool isFile(QJsonValue remoteObject);
    bool isFolder(QJsonValue remoteObject);


    QString getRoot();// return root id  of google drive


    //=== REMOTE FUNCTIONS BLOCK ===

    // download file from cloud
    bool remote_file_get(MSFSObject* object);
    // upload new file to cloud
    bool remote_file_insert(MSFSObject* object);
    // update existing file on cloud
    bool remote_file_update(MSFSObject* object);
    // Generates a set of file IDs which can be provided in insert requests
    bool remote_file_generateIDs(int count);
    // create folder on remote
    bool remote_file_makeFolder(MSFSObject* object);
    bool remote_file_makeFolder(MSFSObject* object,QString parentID);
    // trash file or folder on remote
    bool remote_file_trash(MSFSObject* object);
    // create directory on remote, recursively if nesessary
    bool remote_createDirectory(QString path);


    //=== LOCAL FUNCTION BLOCK ===

    // create directory on local, recursively if nesessary
    void local_createDirectory(QString path);
    void local_removeFile(QString path);
    void local_removeFolder(QString path);



    bool readRemote(QString parentId, QString currentPath);
    bool readLocal(QString path);

public:
    MSGoogleDrive();

     bool auth();
     void saveTokenFile(QString path);  // reimplemented from MSCloudProvider
     bool loadTokenFile(QString path);  // reimplemented from MSCloudProvider
     bool refreshToken();               // reimplemented from MSCloudProvider
     void loadStateFile();              // reimplemented from MSCloudProvider
     void saveStateFile();              // reimplemented from MSCloudProvider

     bool testReplyBodyForError(QString body); // reimplemented from MSCloudProvider
     QString getReplyErrorString(QString body);   // reimplemented from MSCloudProvider


     bool createSyncFileList();

     QHash<QString,MSFSObject> getRemoteFileList();

     bool filterGoogleDocsMimeTypes(QString mime);
     bool filterOfficeMimeTypes(QString mime);


     void doSync();

     QHash<QString,MSFSObject>      filelist_getFSObjectsByState(MSFSObject::ObjectState state);

     QHash<QString,MSFSObject>      filelist_getFSObjectsByState(QHash<QString,MSFSObject> fsObjectList,MSFSObject::ObjectState state);

     QHash<QString,MSFSObject>      filelist_getFSObjectsByTypeLocal(MSLocalFSObject::Type type);

     QHash<QString,MSFSObject>      filelist_getFSObjectsByTypeRemote(MSRemoteFSObject::Type type);

     MSFSObject::ObjectState        filelist_defineObjectState(MSLocalFSObject local, MSRemoteFSObject remote);

     bool                           filelist_FSObjectHasParent(MSFSObject fsObject);

     MSFSObject                     filelist_getParentFSObject(MSFSObject fsObject);

     void                           filelist_populateChanges(MSFSObject changedFSObject);

     // remote files hash table
     QHash<QString,QJsonValue>driveJSONFileList;

     // sync local and remote filesystems hash table
     QHash<QString,MSFSObject> syncFileList;

     bool directUpload(QString url,QString remotePath);

     QString getInfo(); // get info about cloud

public slots:

    bool onAuthFinished(QString html, MSCloudProvider *provider);

};

#endif // MSGOOGLEDRIVE_H
