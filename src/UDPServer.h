/**
 * @file UDPServer.h
 * @brief
 * @author Paco Dupont
 * @version 0.1
 * @date 19 avril 2017
 */

#ifndef SRC_UDPSERVER_H_
#define SRC_UDPSERVER_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Agent.h"
#include "SocialPlanner.h"

/**
 * @class UDPServer
 * @brief This class manage the UDP Server sending computed data to a visualization software
 * and receiving Agent data from other sensor sources
 */
class UDPServer {
public:

	/**
	 * @brief Constructor
	 *
	 * Constructor of the UDPServer class
	 *
	 * @param port : The server port
	 * @param sPlanner : The SocialPlanner connected to this server
	 */
	UDPServer(int port, SocialPlanner * sPlanner);

	/**
	 * @brief Destructor
	 *
	 * Destructor of the UDPServer class
	 */
	virtual ~UDPServer();

	/**
	 * @brief Launch the UDPServer receive function in a new thread
	 *
	 * @return The thread created
	 */
	std::thread spawn();

	/**
	 * @brief Parse the data received by the receive thread
	 *
	 * @return A positive number if parse was successful, 0 otherwise
	 */
	int parse();

	/**
	 * @brief Parse frame0 containing Agent data
	 *
	 * @return The number of Agent parsed
	 */
	int parse_frame0();

	/**
	 * @brief Create frame0 containing all Agent data from the Population
	 *
	 * @return 0
	 */
	int send_frame0();

	/**
	 * @brief Create frame1 containing the Robot data
	 *
	 * @return 0
	 */
	int send_frame1();

	/**
	 * @brief Create frame2 containing Robot path
	 *
	 * @return 0
	 */
	int send_frame2();

	/**
	 * @brief Create frame3 containing Formation data
	 *
	 * @return 0
	 */
	int send_frame3();

	/**
	 * @brief Read input data on the receive socket
	 *
	 * @return number of Bytes read, 0 or negative value in case of I/O error
	 */
	int do_read();

	/**
	 * @brief Send output data on the send socket
	 *
	 * @param sendBuffer : The data buffer
	 * @param sendBuffer_size : The size of the data buffer
	 *
	 * @return The number of bytes send, 0 or negative value in case of I/O error
	 */
	int do_send(uint8_t * sendBuffer, int sendBuffer_size);

	/**
	 * @brief Parse the received data and send every frame
	 */
	void update();

	/**
	 * @brief The threaded read socket
	 */
	void run();

	/**
	 * @brief Send all the frame
	 */
	void sendAll();

	/**
	 * @brief Update or add Agent to the Population
	 *
	 * @param id : The unique identifier of the Agent
	 * @param x : The x coordinate of the Agent
	 * @param y : The y coordinate of the Agent
	 * @param z : The z coordinate of the Agent
	 * @param theta : The angle of the Agent
	 */
	void updateOrPushAgent(int id, float x, float y, float z, float theta);

protected:
	int portNumber; //!< The port used by the UDP Server
	struct sockaddr_in myAddr; //!< The network information of the server
	struct sockaddr_in fromAddr; //!< The network information of the client

	int udpReceiveSocket; //!< Receive socket file descriptor
	int udpSendSocket; //!< Send socket file descriptor

	const static int recvBuffer_size = 122; //!< Receive buffer size
	uint8_t recvBuffer[recvBuffer_size]; //!< Receive buffer

	SocialPlanner* planner; //!< The related SocialPlanner
};

#endif /* SRC_UDPSERVER_H_ */
