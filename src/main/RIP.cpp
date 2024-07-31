#include <vector>
#include <iostream>

//这段 C++ 代码实现了一个简单的路由表更新功能，适用于基于距离矢量的路由算法（如 RIP）。代码通过 updateRoutingTable 函数来更新现有路由表。下面对代码进行详细解释：
struct Route {
    std::string destinationNetwork;
    int distance;
    std::string nextHop;
};
//Route 结构体用于表示网络路由中的一条路由信息。
//destinationNetwork：目的网络的地址。
//distance：到达目的网络的距离。
//nextHop：到达目的网络的下一跳路由器。

void updateRoutingTable(std::vector<Route>& routingTable, const std::vector<Route>& receivedRoutes, const std::string& sender) {
    for (const auto& receivedRoute : receivedRoutes) {
        Route updatedRoute = {receivedRoute.destinationNetwork, receivedRoute.distance + 1, sender};

        bool isRouteUpdated = false;
        for (auto& route : routingTable) {
            if (route.destinationNetwork == updatedRoute.destinationNetwork) {
                if (route.nextHop == sender) {
                    route.distance = updatedRoute.distance;
                } else if (updatedRoute.distance < route.distance) {
                    route.distance = updatedRoute.distance;
                    route.nextHop = updatedRoute.nextHop;
                }
                isRouteUpdated = true;
            }
        }

        if (!isRouteUpdated) {
            routingTable.push_back(updatedRoute);
        }
    }
}

int main() {
    std::vector<Route> routingTable;
    std::vector<Route> receivedRoutes = {{"192.168.1.0", 1, "Router_X"}};

    updateRoutingTable(routingTable, receivedRoutes, "Router_X");

    // Display the updated routing table.
    for (const auto& route : routingTable) {
        std::cout << "Destination Network: " << route.destinationNetwork
                  << ", Distance: " << route.distance
                  << ", Next Hop: " << route.nextHop << std::endl;
    }

    return 0;
}
