/* The LibVMI Library is an introspection library that simplifies access to 
 * memory in a target virtual machine or in a file containing a dump of 
 * a system's physical memory.  LibVMI is based on the XenAccess Library.
 *
 * This file is part of LibVMI.
 *
 * LibVMI is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * LibVMI is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with LibVMI.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OS_WINDOWS_H_
#define OS_WINDOWS_H_

#include "libvmi.h"

struct windows_instance {
    addr_t ntoskrnl; /**< base phys address for ntoskrnl image */

    addr_t ntoskrnl_va; /**< base virt address for ntoskrnl image */

    addr_t kdversion_block; /**< kernel virtual address for start of KdVersionBlock structure */

    addr_t sysproc; /**< physical address for the system process */

    uint64_t tasks_offset; /**< EPROCESS->ActiveProcessLinks */

    uint64_t pdbase_offset; /**< EPROCESS->Pcb.DirectoryTableBase */

    uint64_t pid_offset; /**< EPROCESS->UniqueProcessId */

    uint64_t pname_offset; /**< EPROCESS->ImageFileName */

    win_ver_t version; /**< version of Windows */
};
typedef struct windows_instance *windows_instance_t;

status_t windows_init(vmi_instance_t instance);

addr_t windows_pid_to_pgd(vmi_instance_t vmi, vmi_pid_t pid);
vmi_pid_t windows_pgd_to_pid(vmi_instance_t vmi, addr_t pgd);

status_t
windows_kernel_symbol_to_address(vmi_instance_t vmi, const char *symbol,
        addr_t *kernel_base_address, addr_t *address);
status_t
windows_export_to_rva(vmi_instance_t vmi, vmi_pid_t pid, addr_t base_vaddr,
        const char *symbol, addr_t *rva);
char*
windows_rva_to_export(vmi_instance_t vmi, addr_t rva, addr_t base_vaddr,
        vmi_pid_t pid);

typedef int (*check_magic_func)(uint32_t);
int find_pname_offset(vmi_instance_t vmi, check_magic_func check);
addr_t windows_find_eprocess_list_pid(vmi_instance_t vmi, vmi_pid_t pid);
addr_t windows_find_eprocess_list_pgd(vmi_instance_t vmi, addr_t pgd);


#endif /* OS_WINDOWS_H_ */
