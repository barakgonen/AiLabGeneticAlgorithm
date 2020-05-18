//
// Created by barak on 30/04/2020.
//

#ifndef AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
#define AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H


#include "nQueensGenericSolver.h"
#include "nQueensGeneticAlgoStruct.h"
#include "../../genetic_solver/include/AbstractGeneticSolver.h"
#include "../../genetic_solver/include/MutationOperators.h"

//static const int S = 40;
struct ga_structsss
{
    // in queens[i]=j => the queen is in column i, row j
    std::vector<int> queens;						// the string
//    int queens[S];
    unsigned int fitness;			// its fitness
};
typedef std::vector<ga_structsss> ga_vectorrr;// for brevity

class nQueensGeneticSolver : public nQueensGenericSolver/*, public AbstractGeneticSolver<nQueensGeneticAlgoStruct>*/{
public:
    nQueensGeneticSolver(const NqBoard& board,
                         const SelectionMethod selectionMethod,
                         const CrossoverMethod crossoverMethod,
                         const MutationOperator mutationOperator);

protected:
//    void ox(const int i) override;
//    std::string getBestGene() const override;
//    void handle_specific_elitism(const int index) override;
//    void pmx(const int i) override;
//    int start_solve() override;
//    int get_input_size() override;
//    void init_population() override;
//    void calc_fitness() override;
//    void mutate(nQueensGeneticAlgoStruct &member) override;
//    void set_data_in_buffer_vec_for_single_point_selection(const int indexInBuffer, const int startIndex,
//                                                            const int endIndex, int spos, int tsize) override;
//    void set_data_in_buffer_vec_for_two_points_selection(const int indexInBuffer, const int startIndex,
//                                                         const int endIndex, int spos, int spos2, int tsize) override;
//
    int runSolver() override;
//    void print_results() override;




    void init_population(ga_vectorrr& population,
                         ga_vectorrr& buffer);
    void calc_fitness(ga_vectorrr& population);
    inline void sort_by_fitness(ga_vectorrr& populations)
    {
        sort(populations.begin(), populations.end(), [](ga_structsss& x, ga_structsss& y){return x.fitness < y.fitness;});
    };
    void elitism(ga_vectorrr& population,
                 ga_vectorrr& buffer, int esize);
    void mutate(ga_structsss& member);
    int contain(ga_structsss& member, int num);
    void mate(ga_vectorrr& population, ga_vectorrr& buffer);
    inline void print_board(ga_vectorrr& gav);
    inline void swap(ga_vectorrr*& population,
                     ga_vectorrr*& buffer);
    inline void print_best(ga_vectorrr& gav)
    {
        std::cout << "Best: " << " (" << gav[0].fitness << ")" << std::endl;
    }
    MutationOperator mutataionOperator;
    const int N;
};


#endif //AILABGENETICALGORITHM_NQUEENSGENETICSOLVER_H
