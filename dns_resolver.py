import dns.resolver


def dns_lookup(domain):
    try:
        # Resolve the A record (IPv4 address) for the domain
        result = dns.resolver.resolve(domain, 'A')
        for ip in result:
            print(f'{domain} resolves to {ip.address}')
    except dns.resolver.NoAnswer:
        print(f'No A record found for {domain}')
    except dns.exception.DNSException as e:
        print(f'DNS lookup failed: {e}')


# Specify the domain to lookup
domain = 'www.brainstormtech.com.br'

# Perform DNS lookup for the domain
dns_lookup(domain)
