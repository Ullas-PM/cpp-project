// CommunicationSocket.cpp : implementation file
//

#include "pch.h"
#include "PatientAppMod.h"
#include "CommunicationSocket.h"


// CCommunicationSocket
/// <summary>
/// default constructor
/// </summary>
CCommunicationSocket::CCommunicationSocket()
{
}
/// <summary>
/// destructor
/// </summary>
CCommunicationSocket::~CCommunicationSocket()
{
}
/// <summary>
/// function to create the communication socket
/// </summary>
void CCommunicationSocket::CreateCommunicationSocket()
{
	Create();
}
/// <summary>
/// function to connect the socket to a server socket
/// </summary>
/// <param name="sIP">server ip address</param>
/// <param name="nPortNumber">server port number</param>
BOOL CCommunicationSocket::ConnectToServer(CString& sIP, int& nPortNumber)
{
	return Connect(sIP, nPortNumber);
}


// CCommunicationSocket member functions
