//---------------------------------------------------------------------------------------
//
// Project: DirectionalityIndicator
//
// Copyright 2014-2015 Sebastian Eichelbaum (http://www.sebastian-eichelbaum.de)
//           2014-2015 Max Planck Research Group "Neuroanatomy and Connectivity"
//
// This file is part of DirectionalityIndicator.
//
// DirectionalityIndicator is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DirectionalityIndicator is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with DirectionalityIndicator. If not, see <http://www.gnu.org/licenses/>.
//
//---------------------------------------------------------------------------------------

#include <string>

#include <QWidget>
#include <QToolBox>

#include <di/core/Algorithm.h>

#include <di/gui/Application.h>
#include <di/gui/AlgorithmStrategy.h>

#include "AlgorithmStrategies.h"

#define LogTag "gui/AlgorithmStrategies"
#include <di/core/Logger.h>

namespace di
{
    namespace gui
    {
        AlgorithmStrategies::AlgorithmStrategies( QWidget* parent ):
            QToolBox( parent )
        {
            // Init
            connect( this, SIGNAL( currentChanged( int ) ), this, SLOT( onStrategyChange( int ) ) );
        }

        AlgorithmStrategies::~AlgorithmStrategies()
        {
        }

        void AlgorithmStrategies::prepareProcessingNetwork()
        {
            for( auto s : m_strategies )
            {
                s->prepareProcessingNetwork();
            }
        }

        AlgorithmStrategy* AlgorithmStrategies::addStrategy( AlgorithmStrategy* strategy )
        {
            m_strategies.push_back( strategy );
            addItem( strategy, strategy->getName() );
            onStrategyChange( currentIndex() );
            return strategy;
        }

        void AlgorithmStrategies::onStrategyChange( int index )
        {
            int idx = 0;
            for( auto s : m_strategies )
            {
                s->setActive( index == idx );
                idx++;
            }

            // Change the activate state -> rerun network. Note that during construction , the network might not yet exist.
            if( Application::getProcessingNetwork() )
            {
                Application::getProcessingNetwork()->runNetwork();
            }
        }

        void AlgorithmStrategies::connectToAll( ConstSPtr< di::core::Algorithm > from, std::string outputName,
                                                std::string inputName )
        {
            for( auto s : m_strategies )
            {
                s->connect( from, outputName, inputName );
            }
        }
    }
}

