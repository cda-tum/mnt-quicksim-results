//
// Created by Jan Drewniok on 01.01.23.
//

#include <fiction/algorithms/simulation_sidb/quicksim.hpp>
#include <fiction/io/read_sqd_layout.hpp>  // reader for SiDB layouts including surface scan data
#include <fiction/technology/charge_distribution_surface.hpp>
#include <fiction/types.hpp>                    // pre-defined types suitable for the FCN domain
#include <filesystem>
#include <array>

using namespace fiction;

int main() // NOLINT
{
    const std::string folder = fmt::format("{}/bestagon_gates/and/", EXPERIMENTS_PATH);

        for (const auto& file : std::filesystem::directory_iterator(folder))
        {
            const auto& benchmark = file.path();

            const auto                     lyt = read_sqd_layout<sidb_cell_clk_lyt_siqad>(benchmark.string());

            const quicksim_params          params{sidb_simulation_parameters{2, -0.32}};

            charge_distribution_surface<sidb_cell_clk_lyt_siqad> chargelyt{lyt};

            quicksim_stats<sidb_cell_clk_lyt_siqad> collect{};

            quicksim<sidb_cell_clk_lyt_siqad>(chargelyt, params, &collect);
            collect.report();
        }
    return EXIT_SUCCESS;
}
