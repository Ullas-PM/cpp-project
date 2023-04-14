#pragma once

// CCommunicationSocket command target

class CCommunicationSocket : public CSocket
{
public:
	/// <summary>
	/// default constructor
	/// </summary>
	CCommunicationSocket();
	/// <summary>
	/// destructor
	/// </summary>
	virtual ~CCommunicationSocket();

	/// <summary>
	/// function to create the communication socket
	/// </summary>
	void CreateCommunicationSocket();

	/// <summary>
	/// function to connect the socket to a server socket
	/// </summary>
	/// <param name="sIP">server ip address</param>
	/// <param name="nPortNumber">server port number</param>
	BOOL ConnectToServer(CString& sIP, int& nPortNumber);
};


