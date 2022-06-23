#pragma once

#include <vector>

#include "Graph.h"

std::vector<std::vector<Graph::VertexT>> tarjanFindComponents(Graph const& graph);
