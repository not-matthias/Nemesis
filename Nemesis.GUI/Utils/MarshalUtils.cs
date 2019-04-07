using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Nemesis.Utils
{
    internal class MarshalUtils
    {
        public static T GetStructFromMemory<T>(IntPtr structPtr) where T : struct
        {
            //
            // Create the structure
            //
            var structure = Marshal.PtrToStructure<T>(structPtr);

            //
            // Release the memory
            //
            Marshal.FreeHGlobal(structPtr);

            return structure;
        }
    }
}