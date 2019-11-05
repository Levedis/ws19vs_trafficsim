#include "Sensor.h"

Sensor::Sensor(const string &type, const float &val, const string &unit) {
    srand(time(nullptr));
    m_type = type;
    m_measurement.val = val;
    m_measurement.unit = unit;

    // init own port by random port number
    m_client_port = static_cast<size_t>(rand() % 1000);

    if ((m_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        throw std::invalid_argument("ERROR: failed to create a UDP socket\n");

    createUDPSocket(m_client_port);
}

/**
 * @function declare the struct sockaddr_in from netinet/in.h:
 * {sin_family, sin_port, sin_addr.s_addr}; htons(0) pick any available port
 * @param port adress
 */
sockaddr_in Sensor::createUDPSocket(const unsigned int &port) {
    sockaddr_in socket_addr;

    memset((char *) &socket_addr, 0, sizeof(socket_addr));
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_port = htons(port);
    socket_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    m_ip = inet_ntoa(socket_addr.sin_addr);
    return socket_addr;
}

void Sensor::sendData(char **argv) {
    sockaddr_in server_addr = createUDPSocket(m_server_port);

    // repeatedly send data
    while (true) {

        formatAllSensorData();
        cout << "Sending...\n" << m_buf << endl;

        // send message to the dedicated server
        m_result = sendto(m_socket, m_buf, MAX_LENGTH, 0, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));

        if (m_result < 0) throw std::invalid_argument("ERROR_failed to send message\n");

        if (receivedDataFromServer(server_addr))
            std::cout << "=== Message sent successfully ===\n" << m_buf << std::endl;
        memset(m_buf, 0, sizeof(m_buf)); // clear char array
        sleep(TIME_OUT); // time_out for x secs
    }
}

/**
 * @function check the servers response
 * if the received data on the server side matches the sent client message
 * and whether the server is responding at all within the maximum waiting timespan,
 * trigger a client timeout otherwise
 */
bool Sensor::receivedDataFromServer(const sockaddr_in &server_addr) {
    int addr_len = sizeof(struct sockaddr_in);
    char recv_msg[MAX_LENGTH];

    std::stringstream error_msg;

    // stops sending new messages if server does not respond within TIME_OUT seconds
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char *) &timeout,
               sizeof(struct timeval)); // time_out after 5min of not receiving any message

    // receive server data
    int m_result = recvfrom(m_socket, recv_msg, MAX_LENGTH, 0, (struct sockaddr *) &server_addr,
                            (socklen_t *) &addr_len);

    if (m_result < 0) {
        error_msg << "TIME OUT: server did not respond within " << TIME_OUT << "s\n";
        close(m_socket); // close socket

        throw std::invalid_argument(error_msg.str());
    }
    return true;
}

void Sensor::formatAllSensorData() {
    std::stringstream datetime, msg;
    const float interval = 10.0;

    msg << "[" << m_ip << ":" << m_client_port << "]" << getType() << ":" << toString() << "\n";

    gen_value(interval);

    strncpy(m_buf, msg.str().c_str(), sizeof(m_buf));
    msg.str(std::string());
}

// generate new value randomly between range with upper_bound
void Sensor::gen_value(const float &upper_bound) {
    m_measurement.val = rand() % static_cast<int>(m_measurement.val + upper_bound) + 10;
}


std::string Sensor::toString() const {
    stringstream stream, s_clock;

    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    s_clock << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");

    stream << s_clock.str() <<"\n"<< m_measurement.val << " " << m_measurement.unit;
    return stream.str();
}

Sensor::~Sensor() {

    delete this;
}
