//
// Created by Jan Drewniok on 18.01.23.
//

#include <fiction/algorithms/simulation_sidb/TTS.hpp>
#include <fiction/algorithms/simulation_sidb/exhaustive_ground_state_simulation.hpp>
#include <fiction/io/read_sqd_layout.hpp>  // reader for SiDB layouts including surface scan data
#include <fiction/technology/charge_distribution_surface.hpp>
#include <fiction/types.hpp>  // pre-defined types suitable for the FCN domain

#include <array>
#include <filesystem>

using namespace fiction;

int main() // NOLINT
{

    const std::string folder = fmt::format("{}/bestagon_gates/and/", EXPERIMENTS_PATH);

        for (const auto& file : std::filesystem::directory_iterator(folder))
        {
            const auto& benchmark = file.path();

            const auto                                         lyt = read_sqd_layout<sidb_cell_clk_lyt_siqad>(benchmark.string());
            const sidb_simulation_parameters                   params{2, -0.32};
            charge_distribution_surface<sidb_cell_clk_lyt_siqad> chargelyt{lyt};


            exgs_stats<sidb_cell_clk_lyt_siqad> stats{};
            exgs<sidb_cell_clk_lyt_siqad>(chargelyt, params, &stats);
            stats.report();
        }
    return EXIT_SUCCESS;
}
