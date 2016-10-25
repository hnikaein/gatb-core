//! [snippet1]

/********************************************************************************/
/*                                                                              */
/*       De Bruijn graph: exploring node neighbours                             */
/*                                                                              */
/********************************************************************************/

// We include what we need for the test
#include <gatb/gatb_core.hpp>

#undef NDEBUG
// in this code, we use assert() to check some values
#include <cassert>

/********************************************************************************/
//START application
int main (int argc, char* argv[])
{
  try
  {
    // We create the graph with a bank holding one sequence and use a 
    // specific kmer size and kmer solid abundance set to 1.
    // Using such a string and kmer size we only have two possible nodes
    // in the De Bruijn graph: AATG and ATGC.
    // Of course, in real life we'll load DNA reads from a Fasta/Fastq file.
    Graph graph = Graph::create (
      new BankStrings ("AATGC", NULL), 
      "-kmer-size 4 -abundance-min 1 -verbose 0");

    // We get an iterator for all nodes of the graph.
    Graph::Iterator<Node> it = graph.iterator();

    // We check that we have only two possible nodes
    assert (it.size() == 2);

    // We iterate over nodes.
    for (it.first(); !it.isDone(); it.next())
    {
      // We get a node
      Node& current = it.item();

      // We get the ascii representation of the current iterated node
      std::string s = graph.toString (current);

      // We check that it is correct.
      assert (s=="AATG" || s=="ATGC");

      // Then we analyse one of the node
      if (s=="AATG")
      {
        // We get the neighbors of this specific current
        Graph::Vector<Node> neighbors = graph.successors(current);

        // We check that we got only one successor
        assert (neighbors.size() == 1);

        // Another way to check the number of successors
        assert (graph.outdegree(current) == 1);

        // We check the number of predecessors
        assert (graph.indegree(current) == 0);

        // We check this is the correct neighbor
        assert (graph.toString(neighbors[0]) == "ATGC");
      }
    }

    std::cout << "Graph exploration OK" << std::endl;
  }
  catch (Exception& e)
  {
    std::cerr << "EXCEPTION: " << e.getMessage() << std::endl;
  }

  return EXIT_SUCCESS;
}
//! [snippet1]
