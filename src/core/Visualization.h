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

#ifndef VISUALIZATION_H
#define VISUALIZATION_H

#include <atomic>

#include "Types.h"

namespace di
{
    namespace core
    {
        /**
         * Interface to define the basic operations of all visualizations. If your algorithm wants to output graphics, derive from this class and
         * implement the methods accordingly. The calling order will always be prepare(), loop: update(), render() and finally: finalize().
         */
        class Visualization
        {
        public:
            /**
             * Prepare your visualization. This includes creation of resources, buffers, and others.
             * If an error occurs, throw an exception accordingly.
             *
             * \note this runs in the OpenGL thread and the context is bound.
             */
            virtual void prepare() = 0;

            /**
             * This method is called between the frames. Use this to update resources. Immediately return if nothing needs to update. If you do not
             * want to update anything at all, do not overwrite.
             * If an error occurs, throw an exception accordingly.
             *
             * \note this runs in the OpenGL thread and the context is current.
             */
            virtual void update();

            /**
             * Do actual rendering.
             * If an error occurs, throw an exception accordingly.
             *
             * \note this runs in the OpenGL thread and the context is current.
             */
            virtual void render() = 0;

            /**
             * Finalize your OpenGL resources here. Free buffers and shaders.
             * If an error occurs, throw an exception accordingly.
             *
             * \note this runs in the OpenGL thread and the context is bound.
             */
            virtual void finalize() = 0;

            /**
             * Request an update of the rendering. Since the rendering system is not permanently updating/rendering, this is needed to force a
             * wake-up.
             */
            virtual void renderRequest();

            /**
             * Is an update()/render() cycle requested?
             *
             * \return true if graphics need a refresh.
             */
            virtual bool isRenderingRequested() const;
        protected:
            /**
             * Constructor.
             */
            Visualization();

            /**
             * Destructor.
             */
            virtual ~Visualization();
        private:
            /**
             * A rendering was requested.
             */
            std::atomic< bool > m_renderingRequested;
        };
    }
}

#endif  // VISUALIZATION_H

