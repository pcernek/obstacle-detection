#include "ImageFeedZmq.h"

ImageFeedZmq::ImageFeedZmq(zmq::context_t &ctx) :
    m_ctx(ctx), m_socket(NULL) {

}

ImageFeedZmq::~ImageFeedZmq() {
    if (m_socket != NULL) {
        delete m_socket;
    }
}

bool ImageFeedZmq::init(const std::string &portNum) {
    // Create the socket
    m_socket = new zmq::socket_t(m_ctx, ZMQ_PUB);

    std::string zmq_base = "tcp://*:";

    // Bind the socket
    m_socket->bind( (zmq_base.append(portNum)).c_str() );


    // Apparently this always succeeds
    return true;
}

bool ImageFeedZmq::sendFrame(const std::string &message) {

    zmq::message_t msg(message.c_str(), message.size());

    // Send the message
    return m_socket->send(msg);
}

void ImageFeedZmq::zmqFree(void *data, void *hint) {
    free(data);
}
