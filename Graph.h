#pragma once

#include <memory>
#include <unordered_set>

class Graph {
public:
	using VertexT = int;

	Graph(std::size_t const nVertices)
		:
		ReachableVertices(std::make_unique<std::unordered_set<VertexT>[]>(nVertices)),
		Nvertices(nVertices)
	{}

	void AddEdge(VertexT const from, VertexT const to) {
		this->ReachableVertices[from].insert(to);
	}

	auto const& GetVerticesReachableFrom(VertexT const vertex) const {
		return this->ReachableVertices[vertex];
	}

	std::size_t GetNvertices() const {
		return this->Nvertices;
	}

private:
	std::unique_ptr<std::unordered_set<VertexT>[]> ReachableVertices{};
	std::size_t Nvertices{};
};