#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/netanim-module.h"
#include "ns3/mobility-module.h"

using namespace ns3;
using namespace std;
NS_LOG_COMPONENT_DEFINE ("EcmpExample");

int 
main (int argc, char *argv[])
{
  uint32_t ecmpMode = 2;
  uint32_t socket = 0;

  LogComponentEnable("Ipv4GlobalRouting", LOG_DEBUG);
  LogComponentEnable("Ipv4GlobalRouting", LOG_ERROR);
  LogComponentEnable("EcmpExample", LOG_ALL);


  // Allow the user to override any of the defaults and the above
  // Bind ()s at run-time, via command-line arguments
  CommandLine cmd;
  cmd.AddValue ("EcmpMode", "EcmpMode: (0 none, 1 random, 2 flow, 3 Round_Robin)", ecmpMode);
  cmd.AddValue ("Socket", "Socket: (0 UDP, 1 TCP)", socket);
  cmd.Parse (argc, argv);

  switch (ecmpMode)
    {
      case 0:
        break;
      case 1:
        Config::SetDefault ("ns3::Ipv4GlobalRouting::EcmpMode", StringValue ("ECMP_RANDOM"));
        break;
      case 2:
        Config::SetDefault ("ns3::Ipv4GlobalRouting::EcmpMode", StringValue ("ECMP_HASH"));
        break;  
      case 3:
        Config::SetDefault ("ns3::Ipv4GlobalRouting::EcmpMode", StringValue ("ECMP_RoundRobin"));
        break;
      default:
        NS_FATAL_ERROR ("Illegal command value for EcmpMode: " << ecmpMode);
        break;
    }

  NS_LOG_INFO ("Create nodes.");
  NodeContainer c;
  c.Create (8);

  NodeContainer n0n1 = NodeContainer (c.Get (0), c.Get (1));
  NodeContainer n0n2 = NodeContainer (c.Get (0), c.Get (2));
  NodeContainer n0n3 = NodeContainer (c.Get (0), c.Get (3));
  NodeContainer n0n4 = NodeContainer (c.Get (0), c.Get (4));

  NodeContainer n1n5 = NodeContainer (c.Get (1), c.Get (5));
  NodeContainer n1n6 = NodeContainer (c.Get (1), c.Get (6));

  NodeContainer n2n5 = NodeContainer (c.Get (2), c.Get (5));
  NodeContainer n2n6 = NodeContainer (c.Get (2), c.Get (6));

  NodeContainer n3n5 = NodeContainer (c.Get (3), c.Get (5));
  NodeContainer n3n6 = NodeContainer (c.Get (3), c.Get (6));

  NodeContainer n4n5 = NodeContainer (c.Get (4), c.Get (5));
  NodeContainer n4n6 = NodeContainer (c.Get (4), c.Get (6));

  NodeContainer n5n7 = NodeContainer (c.Get (5), c.Get (7));
  NodeContainer n6n7 = NodeContainer (c.Get (6), c.Get (7));

  //int x = 0;
  int y = 0;
  for (uint32_t i = 0; i < c.GetN(); i++)
    {
      Ptr<ConstantPositionMobilityModel> loc = CreateObject<ConstantPositionMobilityModel>();
      c.Get(i)->AggregateObject(loc);

      if (i == 0)
        loc->SetPosition(Vector(1, 5, 0));
      else if (i == 1 || i == 2 || i == 3 || i == 4)
        {
          y += 2;
          loc->SetPosition(Vector(10, y, 0));
        }
      else if (i == 5 || i == 6)
        {
          y -= 2;
          loc->SetPosition(Vector(20, y, 0));
        }
      else if (i == 7)
        loc->SetPosition(Vector(23, 5, 0));
    }


  InternetStackHelper internet;
  internet.Install (c);

  NS_LOG_INFO ("Create channels.");
  PointToPointHelper p2p;
  p2p.SetDeviceAttribute ("DataRate", StringValue ("10Mbps"));
  p2p.SetChannelAttribute ("Delay", StringValue ("1ms"));

  NetDeviceContainer d0d1 = p2p.Install (n0n1);
  NetDeviceContainer d0d2 = p2p.Install (n0n2);
  NetDeviceContainer d0d3 = p2p.Install (n0n3);
  NetDeviceContainer d0d4 = p2p.Install (n0n4);

  NetDeviceContainer d1d5 = p2p.Install (n1n5);
  NetDeviceContainer d1d6 = p2p.Install (n1n6);

  NetDeviceContainer d2d5 = p2p.Install (n2n5);
  NetDeviceContainer d2d6 = p2p.Install (n2n6);

  NetDeviceContainer d3d5 = p2p.Install (n3n5);
  NetDeviceContainer d3d6 = p2p.Install (n3n6);

  NetDeviceContainer d4d5 = p2p.Install (n4n5);
  NetDeviceContainer d4d6 = p2p.Install (n4n6);

  NetDeviceContainer d5d7 = p2p.Install (n5n7);
  NetDeviceContainer d6d7 = p2p.Install (n6n7);


  NS_LOG_INFO ("Assign IP Addresses.");
  Ipv4AddressHelper ipv4;
  ipv4.SetBase ("10.0.1.0", "255.255.255.0");
  ipv4.Assign (d0d1);
  ipv4.SetBase ("10.0.2.0", "255.255.255.0");
  ipv4.Assign (d0d2);
  ipv4.SetBase ("10.0.3.0", "255.255.255.0");
  ipv4.Assign (d0d3);
  ipv4.SetBase ("10.0.4.0", "255.255.255.0");
  ipv4.Assign (d0d4);

  ipv4.SetBase ("10.1.5.0", "255.255.255.0");
  ipv4.Assign (d1d5);
  ipv4.SetBase ("10.1.6.0", "255.255.255.0");
  ipv4.Assign (d1d6);

  ipv4.SetBase ("10.2.5.0", "255.255.255.0");
  ipv4.Assign (d2d5);
  ipv4.SetBase ("10.2.6.0", "255.255.255.0");
  ipv4.Assign (d2d6);

  ipv4.SetBase("10.3.5.0", "255.255.255.0");
  ipv4.Assign(d3d5);
  ipv4.SetBase("10.3.6.0", "255.255.255.0");
  ipv4.Assign(d3d6);

  ipv4.SetBase("10.4.5.0", "255.255.255.0");
  ipv4.Assign(d4d5);
  ipv4.SetBase("10.4.6.0", "255.255.255.0");
  ipv4.Assign(d4d6);

  ipv4.SetBase("10.5.7.0", "255.255.255.0");
  ipv4.Assign(d5d7);
  ipv4.SetBase("10.6.7.0", "255.255.255.0");
  ipv4.Assign(d6d7);

  NS_LOG_INFO ("Populate routing tables.");
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  NS_LOG_INFO ("Create Applications.");
  if (socket == 0)
    {
      uint16_t port = 9;   // Discard port (RFC 863)
      OnOffHelper onoff("ns3::UdpSocketFactory", InetSocketAddress(Ipv4Address("10.5.7.2"), port));
      onoff.SetConstantRate(DataRate("100kbps"));
      onoff.SetAttribute("PacketSize", UintegerValue(500));

      ApplicationContainer apps;
      for (uint32_t i = 0; i < 10; i++)
        {
          apps.Add(onoff.Install(c.Get(0)));
        }

      apps.Start(Seconds(0.0));
      apps.Stop(Seconds(1.0));

      PacketSinkHelper sink("ns3::UdpSocketFactory", Address(InetSocketAddress(Ipv4Address::GetAny(), port)));
      sink.Install(c.Get(7));
  }
  else if (socket == 1)
    {
      uint16_t port = 1500;
      BulkSendHelper source("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address("10.6.7.2"), port));

      ApplicationContainer sourceApps;
      for (uint32_t i = 0; i < 5; i++)
        {
          sourceApps.Add(source.Install(c.Get(0)));
        }

      sourceApps.Start(Seconds(0.0));
      sourceApps.Stop(Seconds(1.0));

      PacketSinkHelper sink("ns3::TcpSocketFactory", InetSocketAddress(Ipv4Address::GetAny(), port));
      ApplicationContainer sinkApps = sink.Install(c.Get(7));
    }

  // Trace the right-most (second) interface on nodes 2, 3, and 4
//  p2p.EnablePcap ("ecmp-global-routing", 2, 2);
//  p2p.EnablePcap ("ecmp-global-routing", 3, 2);
//  p2p.EnablePcap ("ecmp-global-routing", 4, 2);

  AnimationInterface anim("ecmp");
  anim.SetMaxPktsPerTraceFile(100000000);
  for (uint32_t i = 1; i < 7; i++)
        anim.UpdateNodeColor(c.Get(i), 0, 128, 0);
  anim.EnablePacketMetadata(true);

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Run ();
  Simulator::Destroy ();
  NS_LOG_INFO("Simulation is ended!");
}
