// license:BSD-3-Clause
// copyright-holders:Olivier Galibert
#ifndef MAME_EMU_EMUMEM_HEDP_H
#define MAME_EMU_EMUMEM_HEDP_H

#pragma once

// handler_entry_read_delegate/handler_entry_write_delegate

// Executes an access through a delegate, usually containing a handler or a lambda

template<int Width, int AddrShift, typename READ> class handler_entry_read_delegate : public handler_entry_read_address<Width, AddrShift>
{
public:
	using uX = typename emu::detail::handler_entry_size<Width>::uX;

	handler_entry_read_delegate(address_space *space, u16 flags, const READ &delegate) : handler_entry_read_address<Width, AddrShift>(space, flags), m_delegate(delegate) {}
	~handler_entry_read_delegate() = default;

	uX read(offs_t offset, uX mem_mask) const override;
	uX read_interruptible(offs_t offset, uX mem_mask) const override;
	std::pair<uX, u16> read_flags(offs_t offset, uX mem_mask) const override;
	u16 lookup_flags(offs_t offset, uX mem_mask) const override;

	std::string name() const override;

private:
	READ m_delegate;

	template<typename R>
		std::enable_if_t<std::is_same<R, read8_delegate>::value ||
						 std::is_same<R, read16_delegate>::value ||
						 std::is_same<R, read32_delegate>::value ||
						 std::is_same<R, read64_delegate>::value,
						 uX> read_impl(offs_t offset, uX mem_mask) const;

	template<typename R>
		std::enable_if_t<std::is_same<R, read8m_delegate>::value ||
						 std::is_same<R, read16m_delegate>::value ||
						 std::is_same<R, read32m_delegate>::value ||
						 std::is_same<R, read64m_delegate>::value,
						 uX> read_impl(offs_t offset, uX mem_mask) const;

	template<typename R>
		std::enable_if_t<std::is_same<R, read8s_delegate>::value ||
						 std::is_same<R, read16s_delegate>::value ||
						 std::is_same<R, read32s_delegate>::value ||
						 std::is_same<R, read64s_delegate>::value,
						 uX> read_impl(offs_t offset, uX mem_mask) const;

	template<typename R>
		std::enable_if_t<std::is_same<R, read8sm_delegate>::value ||
						 std::is_same<R, read16sm_delegate>::value ||
						 std::is_same<R, read32sm_delegate>::value ||
						 std::is_same<R, read64sm_delegate>::value,
						 uX> read_impl(offs_t offset, uX mem_mask) const;

	template<typename R>
		std::enable_if_t<std::is_same<R, read8mo_delegate>::value ||
						 std::is_same<R, read16mo_delegate>::value ||
						 std::is_same<R, read32mo_delegate>::value ||
						 std::is_same<R, read64mo_delegate>::value,
						 uX> read_impl(offs_t offset, uX mem_mask) const;

	template<typename R>
		std::enable_if_t<std::is_same<R, read8smo_delegate>::value ||
						 std::is_same<R, read16smo_delegate>::value ||
						 std::is_same<R, read32smo_delegate>::value ||
						 std::is_same<R, read64smo_delegate>::value,
						 uX> read_impl(offs_t offset, uX mem_mask) const;
};

template<int Width, int AddrShift, typename WRITE> class handler_entry_write_delegate : public handler_entry_write_address<Width, AddrShift>
{
public:
	using uX = typename emu::detail::handler_entry_size<Width>::uX;

	handler_entry_write_delegate(address_space *space, u16 flags, const WRITE &delegate) : handler_entry_write_address<Width, AddrShift>(space, flags), m_delegate(delegate) {}
	~handler_entry_write_delegate() = default;

	void write(offs_t offset, uX data, uX mem_mask) const override;
	void write_interruptible(offs_t offset, uX data, uX mem_mask) const override;
	u16 write_flags(offs_t offset, uX data, uX mem_mask) const override;
	u16 lookup_flags(offs_t offset, uX mem_mask) const override;

	std::string name() const override;

private:
	WRITE m_delegate;

	template<typename W>
		std::enable_if_t<std::is_same<W, write8_delegate>::value ||
						 std::is_same<W, write16_delegate>::value ||
						 std::is_same<W, write32_delegate>::value ||
						 std::is_same<W, write64_delegate>::value,
						 void> write_impl(offs_t offset, uX data, uX mem_mask) const;

	template<typename W>
		std::enable_if_t<std::is_same<W, write8m_delegate>::value ||
						 std::is_same<W, write16m_delegate>::value ||
						 std::is_same<W, write32m_delegate>::value ||
						 std::is_same<W, write64m_delegate>::value,
						 void> write_impl(offs_t offset, uX data, uX mem_mask) const;

	template<typename W>
		std::enable_if_t<std::is_same<W, write8s_delegate>::value ||
						 std::is_same<W, write16s_delegate>::value ||
						 std::is_same<W, write32s_delegate>::value ||
						 std::is_same<W, write64s_delegate>::value,
						 void> write_impl(offs_t offset, uX data, uX mem_mask) const;

	template<typename W>
		std::enable_if_t<std::is_same<W, write8sm_delegate>::value ||
						 std::is_same<W, write16sm_delegate>::value ||
						 std::is_same<W, write32sm_delegate>::value ||
						 std::is_same<W, write64sm_delegate>::value,
						 void> write_impl(offs_t offset, uX data, uX mem_mask) const;

	template<typename W>
		std::enable_if_t<std::is_same<W, write8mo_delegate>::value ||
						 std::is_same<W, write16mo_delegate>::value ||
						 std::is_same<W, write32mo_delegate>::value ||
						 std::is_same<W, write64mo_delegate>::value,
						 void> write_impl(offs_t offset, uX data, uX mem_mask) const;

	template<typename W>
		std::enable_if_t<std::is_same<W, write8smo_delegate>::value ||
						 std::is_same<W, write16smo_delegate>::value ||
						 std::is_same<W, write32smo_delegate>::value ||
						 std::is_same<W, write64smo_delegate>::value,
						 void> write_impl(offs_t offset, uX data, uX mem_mask) const;
};


// handler_entry_read_ioport/handler_entry_write_ioport

// Accesses an ioport

template<int Width, int AddrShift> class handler_entry_read_ioport : public handler_entry_read<Width, AddrShift>
{
public:
	using uX = typename emu::detail::handler_entry_size<Width>::uX;

	handler_entry_read_ioport(address_space *space, u16 flags, ioport_port *port) : handler_entry_read<Width, AddrShift>(space, flags), m_port(port) {}
	~handler_entry_read_ioport() = default;

	uX read(offs_t offset, uX mem_mask) const override;
	uX read_interruptible(offs_t offset, uX mem_mask) const override;
	std::pair<uX, u16> read_flags(offs_t offset, uX mem_mask) const override;
	u16 lookup_flags(offs_t offset, uX mem_mask) const override;

	std::string name() const override;

private:
	ioport_port *m_port;
};

template<int Width, int AddrShift> class handler_entry_write_ioport : public handler_entry_write<Width, AddrShift>
{
public:
	using uX = typename emu::detail::handler_entry_size<Width>::uX;

	handler_entry_write_ioport(address_space *space, u16 flags, ioport_port *port) : handler_entry_write<Width, AddrShift>(space, flags), m_port(port) {}
	~handler_entry_write_ioport() = default;

	void write(offs_t offset, uX data, uX mem_mask) const override;
	void write_interruptible(offs_t offset, uX data, uX mem_mask) const override;
	u16 write_flags(offs_t offset, uX data, uX mem_mask) const override;
	u16 lookup_flags(offs_t offset, uX mem_mask) const override;

	std::string name() const override;

private:
	ioport_port *m_port;
};

#endif // MAME_EMU_EMUMEM_HEDP_H
