
/******************************************************************************
 *
 *  This file is part of canu, a software program that assembles whole-genome
 *  sequencing reads into contigs.
 *
 *  This software is based on:
 *    'Celera Assembler' (http://wgs-assembler.sourceforge.net)
 *    the 'kmer package' (http://kmer.sourceforge.net)
 *  both originally distributed by Applera Corporation under the GNU General
 *  Public License, version 2.
 *
 *  Canu branched from Celera Assembler at its revision 4587.
 *  Canu branched from the kmer project at its revision 1994.
 *
 *  This file is derived from:
 *
 *    src/AS_BAT/AS_BAT_Outputs.C
 *
 *  Modifications by:
 *
 *    Brian P. Walenz from 2010-NOV-23 to 2014-MAR-31
 *      are Copyright 2010-2014 J. Craig Venter Institute, and
 *      are subject to the GNU General Public License version 2
 *
 *    Brian P. Walenz from 2014-NOV-17 to 2015-JUN-05
 *      are Copyright 2014-2015 Battelle National Biodefense Institute, and
 *      are subject to the BSD 3-Clause License
 *
 *    Brian P. Walenz beginning on 2016-JAN-04
 *      are a 'United States Government Work', and
 *      are released in the public domain
 *
 *    Sergey Koren beginning on 2016-MAR-30
 *      are a 'United States Government Work', and
 *      are released in the public domain
 *
 *  File 'README.licenses' in the root directory of this distribution contains
 *  full conditions and disclaimers for each license.
 */

#include "AS_BAT_ReadInfo.H"
#include "AS_BAT_OverlapCache.H"
#include "AS_BAT_BestOverlapGraph.H"
#include "AS_BAT_Logging.H"

#include "AS_BAT_Unitig.H"

#include "AS_BAT_PlaceReadUsingOverlaps.H"

#include "tgStore.H"



void
writeTigsToStore(TigVector     &tigs,
                 char          *filePrefix,
                 char          *storeName,
                 bool           isFinal) {
  char        filename[FILENAME_MAX] = {0};

  sprintf(filename, "%s.%sStore", filePrefix, storeName);
  tgStore     *tigStore = new tgStore(filename);
  tgTig       *tig      = new tgTig;

  for (uint32 ti=0; ti<tigs.size(); ti++) {
    Unitig  *utg = tigs[ti];

    if ((utg == NULL) || (utg->getNumReads() == 0))
      continue;

    assert(utg->getLength() > 0);

    //  Initialize the output tig.

    tig->clear();

    tig->_tigID           = utg->id();

    tig->_coverageStat    = 1.0;  //  Default to just barely unique
    tig->_microhetProb    = 1.0;  //  Default to 100% probability of unique

    //  Set the class.

    if      (utg->_isUnassembled == true)
      tig->_class = tgTig_unassembled;

    //  Disabled, because bogart is not finding most of the true bubbles.
    //else if (utg->_isBubble == true)
    //  tig->_class = tgTig_bubble;

    else
      tig->_class = tgTig_contig;

    tig->_suggestRepeat   = (utg->_isRepeat   == true);
    tig->_suggestCircular = (utg->_isCircular == true);

    tig->_layoutLen       = utg->getLength();

    //  Transfer reads from the bogart tig to the output tig.

    resizeArray(tig->_children, tig->_childrenLen, tig->_childrenMax, utg->ufpath.size(), resizeArray_doNothing);

    for (uint32 ti=0; ti<utg->ufpath.size(); ti++) {
      ufNode        *frg   = &utg->ufpath[ti];

      tig->addChild()->set(frg->ident,
                           frg->parent, frg->ahang, frg->bhang,
                           frg->position.bgn, frg->position.end);
    }

    //  And write to the store

    tigStore->insertTig(tig, false);
  }

  delete    tig;
  delete    tigStore;
}
