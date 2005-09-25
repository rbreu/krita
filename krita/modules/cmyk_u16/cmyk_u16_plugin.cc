/*
* cmyk_u16_plugin.cc -- Part of Krita
*
* Copyright (c) 2004 Boudewijn Rempt (boud@valdyas.org)
* Copyright (c) 2005 Adrian Page <adrian@pagenet.plus.com>
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.
*
*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with this program; if not, write to the Free Software
*  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include <kinstance.h>
#include <kgenericfactory.h>
#include <kdebug.h>

#include <kis_global.h>
#include <kis_colorspace_factory_registry.h>
#include <kis_factory.h>
#include <kis_basic_histogram_producers.h>

#include "cmyk_u16_plugin.h"
#include "kis_cmyk_u16_colorspace.h"

typedef KGenericFactory<CMYKU16Plugin> CMYKU16PluginFactory;
K_EXPORT_COMPONENT_FACTORY( krita_cmyk_u16_plugin, CMYKU16PluginFactory( "krita" ) )


CMYKU16Plugin::CMYKU16Plugin(QObject *parent, const char *name, const QStringList &)
    : KParts::Plugin(parent, name)
{
        setInstance(CMYKU16PluginFactory::instance());

    kdDebug(DBG_AREA_PLUGINS) << "16-bit integer CMYK Color model plugin. Class: "
        << className()
        << ", Parent: "
        << parent -> className()
        << "\n";

    if ( parent->inherits("KisFactory") )
    {
        KisColorSpace * colorSpaceCMYKU16 = new KisCmykU16ColorSpace(0);
        KisColorSpaceFactory * csf = new KisCmykU16ColorSpaceFactory();
        Q_CHECK_PTR(colorSpaceCMYKU16);
        KisColorSpaceFactoryRegistry::instance() -> add(csf);
        KisHistogramProducerFactoryRegistry::instance() -> add(
                new KisBasicHistogramProducerFactory<KisBasicU16HistogramProducer>
                (KisID("CMYK16HISTO", i18n("CMYK16 Histogram")), colorSpaceCMYKU16) );
    }

}

CMYKU16Plugin::~CMYKU16Plugin()
{
}

#include "cmyk_u16_plugin.moc"
