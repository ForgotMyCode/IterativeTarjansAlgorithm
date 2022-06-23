#include "tarjan.h"

#include <iterator>
#include <memory>
#include <stack>

namespace {
	using Vertex = typename Graph::VertexT;
	using IndexT = int;

	constexpr static IndexT UNDEFINED_INDEX = -1;

	struct TarjanSearchNode {
		IndexT Index{UNDEFINED_INDEX}, LowLink{};
		std::unordered_set<Vertex>::const_iterator CurrentNeighbourIt{}, EndNeighbourIt{};
		bool IsOnStack{false};
		bool IsSeenFirstTime{true};
	};
}

static
std::vector<Vertex> createComponent(std::stack<Vertex>& tarjanStack, std::unique_ptr<TarjanSearchNode[]> const& searchNodes, Vertex const vertex) {
	std::vector<Vertex> component{};

	Vertex poppedVertex{};
	do {
		poppedVertex = tarjanStack.top(); tarjanStack.pop();
		searchNodes[poppedVertex].IsOnStack = false;
		component.emplace_back(poppedVertex);
	} while(poppedVertex != vertex);

	return component;
}

static
void tarjanExploreFrom(Graph const& graph, std::vector<std::vector<Vertex>>& components, std::unique_ptr<TarjanSearchNode[]> const& searchNodes, Vertex vertex) {
	std::stack<Vertex> stack{};
	std::stack<Vertex> tarjanStack{};
	stack.push(vertex);

	IndexT index = 0;

	while(!stack.empty()) {
	next: {}

		vertex = stack.top();	stack.pop();

		TarjanSearchNode& currentNode = searchNodes[vertex];

		if(currentNode.IsSeenFirstTime) {
			currentNode.Index = index;
			currentNode.LowLink = index;
			++index;

			currentNode.IsOnStack = true;
			currentNode.IsSeenFirstTime = false;

			currentNode.CurrentNeighbourIt = graph.GetVerticesReachableFrom(vertex).begin();
			currentNode.EndNeighbourIt = graph.GetVerticesReachableFrom(vertex).end();

			tarjanStack.push(vertex);
		}
		else {
			TarjanSearchNode& neighbourNode = searchNodes[*currentNode.CurrentNeighbourIt];
			currentNode.LowLink = std::min(currentNode.LowLink, neighbourNode.LowLink);
			currentNode.CurrentNeighbourIt = std::next(currentNode.CurrentNeighbourIt);
		}

		for(auto& neighbourIt = currentNode.CurrentNeighbourIt; neighbourIt != currentNode.EndNeighbourIt; ++neighbourIt) {
			const Vertex neighbour = *neighbourIt;
			TarjanSearchNode& neighbourNode = searchNodes[neighbour];

			if(neighbourNode.Index == UNDEFINED_INDEX) {
				stack.push(vertex);
				stack.push(neighbour);
				goto next;
			}

			if(neighbourNode.IsOnStack) {
				currentNode.LowLink = std::min(currentNode.LowLink, neighbourNode.Index);
			}
		}

		if(currentNode.LowLink == currentNode.Index) {
			components.emplace_back(createComponent(tarjanStack, searchNodes, vertex));
		}
	}
}

std::vector<std::vector<Vertex>> tarjanFindComponents(Graph const& graph) {
	std::vector<std::vector<Vertex>> components{};
	std::unique_ptr<TarjanSearchNode[]> const searchNodes{std::make_unique<TarjanSearchNode[]>(graph.GetNvertices())};

	for(Vertex vertex = 0; vertex < Vertex(graph.GetNvertices()); ++vertex) {
		if(searchNodes[vertex].Index == UNDEFINED_INDEX) {
			tarjanExploreFrom(graph, components, searchNodes, vertex);
		}
	}

	return components;
}
