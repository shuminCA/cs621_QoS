#include "traffic-class.h"

namespace ns3 {

TrafficClass::TrafficClass(uint32_t packets, uint32_t maxPackets)
    : m_packets(packets), m_maxPackets(maxPackets) {}

TrafficClass::~TrafficClass() {}

void TrafficClass::AddFilter(Filter* filter) {
  m_filters.push_back(filter);
  // std::cout << "TrafficClass: AddFilters() -> size:" << m_filters.size() << std::endl;
}

bool TrafficClass::Match(Ptr<Packet> p) {
    for (auto& filter : m_filters) {
      if (filter->match(p)) {
        return true;
      }
    }
    return false;
}

bool TrafficClass::Enqueue(Ptr<Packet> packet) {
  if (m_packets < m_maxPackets) {
    m_queue.push(packet);
    m_packets++;
    return true;
  } else {
    return false;
  }
}

Ptr<Packet> TrafficClass::Dequeue() {
  if (!m_queue.empty()) {
    Ptr<Packet> packet = m_queue.front();
    m_queue.pop();
    m_packets--;
    return packet;
  }
  return nullptr;
}

Ptr<Packet> TrafficClass::Peek() const{
  if (!m_queue.empty()) {
    Ptr<Packet> packet = m_queue.front();
    return packet;
  }
  return nullptr;
}

bool TrafficClass::IsEmpty() const{ return m_queue.empty(); }

uint32_t TrafficClass::GetQueueSize() { return m_queue.size(); }

uint32_t TrafficClass::GetFilterSize() { return m_filters.size(); }

void TrafficClass::SetDeficit(uint32_t deficit) { m_deficit = deficit; }

void TrafficClass::SetWeight(double weight) { m_weight = weight; }

uint32_t TrafficClass::GetDeficit() const { return m_deficit; }

double_t TrafficClass::GetWeight() const { return m_weight; }
}
